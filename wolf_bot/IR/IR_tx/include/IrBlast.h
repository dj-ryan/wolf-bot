/**
 * file: IrBlast.h
 * version: 0.1
 * author: David Ryan
 * updated: 2020-12-01
 * description: IR blast functions
 */

#define DEFAULT_FREQ 38 // default carrier frequency, in kHz

#define DEFAULT_TX_PIN 17 // IR carrier output

class IrBlast
{
private:
    /* data */
    unsigned char carrierFreq /* = 38 */; // default
    unsigned char txPin /* = 2 */;        // IR carrier output

    bool invertVoltage /* = false */;  // invert the signal
    bool invertBitOrder /* = false */; // invert the bit order

    void assemblyBytes(unsigned long &msg, unsigned char botID, unsigned char blast);
    void irSendNEC(uint32_t code, uint8_t irLedPin, uint8_t freqKhz, bool inverted = false, bool invertedBitOrder = false);
    void wave(uint8_t irLedPin, bool inverted, uint8_t carrierPeriodUs, bool isOn, uint16_t waves);

public:
    IrBlast(/* args */);
    ~IrBlast();

    void setCarrierFreq(unsigned char freq);
    void setTxPin(unsigned char pin);
    void setInvertVoltage(bool invert);
    void setInvertBitOrder(bool invert);

    void blast(unsigned char botId, unsigned char blast, unsigned char repeats);
};

IrBlast::IrBlast(/* args */)
{
    carrierFreq = 38; // default
    txPin = 2;        // IR carrier output

    invertVoltage = false; // invert the signal
    invertBitOrder = false; // invert the bit order

    return;
}

IrBlast::~IrBlast()
{
    return;
}

void IrBlast::setCarrierFreq(unsigned char freq)
{
    carrierFreq = freq;
    return;
}

void IrBlast::setTxPin(unsigned char pin)
{
    txPin = pin;
    return;
}

void IrBlast::setInvertVoltage(bool invert)
{
    invertVoltage = invert;
    return;
}

void IrBlast::setInvertBitOrder(bool invert)
{
    invertBitOrder = invert;
    return;
}

void IrBlast::assemblyBytes(unsigned long &msg, unsigned char botID, unsigned char blast)
{
    msg = 0x00000000; // clear the message

    unsigned short address = 0x0000; // clear the address
    unsigned short command = 0x0000; // clear the command

    address = (botID << 8) | (~botID & 0x00FF); // assemble the address
    command = (blast << 8) | (~blast & 0x00FF); // assemble the command

    msg = (address << 16) | command; // assemble the message

    return;
}

/* Generates a wave given */
void IrBlast::wave(uint8_t irLedPin, bool inverted, uint8_t carrierPeriodUs, bool isOn, uint16_t waves)
{
    // send carrier burst. on = IR mark, otherwise IR space (filler)
    uint32_t burstStartUs = micros();

    for (uint16_t i = 0; i < waves; i++)
    {
        digitalWrite(irLedPin, isOn != inverted ? HIGH : LOW); // Xor. carrier mark or filler
        delayMicroseconds(carrierPeriodUs / 3);                // 33% duty cycle
        digitalWrite(irLedPin, inverted ? HIGH : LOW);         // carrier space
        while (micros() - (burstStartUs + (i * carrierPeriodUs)) < carrierPeriodUs)
            ; // idle until end of wave(i)
    };

    return;
}

void IrBlast::irSendNEC(uint32_t code, uint8_t irLedPin, uint8_t freqKhz, bool inverted, bool invertedBitOrder)
{
    uint16_t NecBurstUnit = (freqKhz * 562L) / 1000L; // IR carrier waves for 1 NEC mark or 1 NEC space( bit 0).
    uint8_t carrierPeriodUs = (int16_t)1000 / freqKhz;
    uint8_t *codeSplit;
    codeSplit = (uint8_t *)&code; // treat uint32_t as byte array ;

    Serial.print(" - code: ");
    Serial.println(code);

    pinMode(irLedPin, OUTPUT);
    wave(irLedPin, inverted, carrierPeriodUs, true, NecBurstUnit * 16); // header mark 9000 us
    wave(irLedPin, inverted, carrierPeriodUs, false, NecBurstUnit * 8); // header space 4500 us
    for (uint8_t i = 0; i < 32; i++)
    {                                                                  // 32 bits
        wave(irLedPin, inverted, carrierPeriodUs, true, NecBurstUnit); // NEC mark
        uint8_t codeByte = !invertedBitOrder ? 3 - i / 8 /*MSB*/ : i / 8 /*LSB*/;
        uint8_t codeBit = !invertedBitOrder ? 7 - i % 8 /*MSB*/ : i % 8 /*LSB*/;
        wave(irLedPin, inverted, carrierPeriodUs, false, bitRead(*(codeSplit + codeByte), codeBit) == 1 ? NecBurstUnit * 3 : NecBurstUnit); // NEC space(0) 562us or NEC space(1) ~1675us
    }
    wave(irLedPin, inverted, carrierPeriodUs, true, NecBurstUnit); // terminator

    return;
} // end of irSendNECblk()

void IrBlast::blast(unsigned char botId, unsigned char blast, unsigned char repeats)
{
    unsigned long msg = 0x00000000; // clear the message

    assemblyBytes(msg, botId, blast); // assemble the message

    Serial.println("Blasting: " + String(msg, HEX)); // debug

    // TODO implement repeats
    // TODO use member vars
    //Serial.println("blasting...");
    irSendNEC(msg, DEFAULT_TX_PIN, DEFAULT_FREQ, false, false);

}
