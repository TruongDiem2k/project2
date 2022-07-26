/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 19/07/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/


#include <mega16.h>
#include <math.h>
#include <stdio.h>
#include <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>

#define ADC_VREF_TYPE 0x40

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);

    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);

    // Start the AD conversion
    ADCSRA|=0x40;

    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;

    return ADCW;
}

// Declare your global variables here
unsigned int adc_value;
float adc_temp;
unsigned char buffer[16], i;

void display(char* buffer, float temp) {
    lcd_clear();
    if ((int) temp > 39) {
        lcd_puts("    CANH BAO    ");

    } else {
        lcd_puts("Nhiet do an toan");
    }
    lcd_gotoxy(0, 1);
    lcd_puts(buffer);
}
void main(void)
{
    // Port A initialization
    PORTA=0x00;
    DDRA=0x00;

    // Port B initialization
    PORTB=0x00;
    DDRB=0x00;

    // Port C initialization
    PORTC=0x00;
    DDRC=0x00;

    // Port D initialization
    PORTD=0x00;
    DDRD=0x01; // Khoi tao mode output cho portD.0 = 1

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    // Mode: Normal top=0xFF
    // OC0 output: Disconnected
    TCCR0=0x00;
    TCNT0=0x00;
    OCR0=0x00;

    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: Timer1 Stopped
    // Mode: Normal top=0xFFFF
    // OC1A output: Discon.
    // OC1B output: Discon.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A=0x00;
    TCCR1B=0x00;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;

    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: Timer2 Stopped
    // Mode: Normal top=0xFF
    // OC2 output: Disconnected
    ASSR=0x00;
    TCCR2=0x00;
    TCNT2=0x00;
    OCR2=0x00;

    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    MCUCR=0x00;
    MCUCSR=0x00;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=0x00;

    // USART initialization
    // USART disabled
    UCSRB=0x00;

    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    ACSR=0x80;
    SFIOR=0x00;

    // ADC initialization
    // ADC Clock frequency: 1000.000 kHz
    // ADC Voltage Reference: AVCC pin
    // ADC Auto Trigger Source: ADC Stopped
    ADMUX=ADC_VREF_TYPE & 0xff;
    ADCSRA=0x84;

    // SPI initialization
    // SPI disabled
    SPCR=0x00;

    // TWI initialization
    // TWI disabled
    TWCR=0x00;

    // Alphanumeric LCD initialization
    // Connections specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTD Bit 6
    // RD - PORTD Bit 5
    // EN - PORTD Bit 7
    // D4 - PORTC Bit 4
    // D5 - PORTC Bit 5
    // D6 - PORTC Bit 6
    // D7 - PORTC Bit 7
    // Characters/line: 16
    lcd_init(16);

    while (1)
    {
        adc_value = read_adc(0);
        adc_temp = adc_value * 500.0f / 1024;
        sprintf(buffer, "Nhiet do: %d", (int)adc_temp);
        display(buffer, adc_temp);

        if ((int) adc_temp > 39) {
            for (i = 0; i < 5; i++) {
                PORTD.0 = 1;
                delay_ms(100);
                PORTD.0 = 0;
                delay_ms(100);
            }
        } else {
            PORTD.0 = 0;
            delay_ms(1000);
        }
    }
}
