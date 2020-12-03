#include <exercicio_um.h>
// 20178440081
const int8 u = 1;
const int8 p = 8;
const int8 a = 0;

const int8 frequencia = 50;

const int8 frequencia_led_tres = u + frequencia;            // 51
const int8 frequencia_led_dois = p + frequencia_led_tres;   // 59
const int8 frequencia_led_um   = a + frequencia_led_dois;   // 59

const int16 a_cada_382_dividido_por_dois_overflow_pisca = (int16)19531.25 / (frequencia_led_tres*2);  // 382.96
const int16 a_cada_331_dividido_por_dois_overflow_pisca = (int16)19531.25 / (frequencia_led_dois*2);  // 331.038


unsigned int16 contador_um=0, contador_dois_tres=0;

// 1000ms/0.0512ms = 19,531.25 qtd de overflow/segundo

#INT_RTCC
void  RTCC_isr(void) 
{   
    contador_um++;
    contador_dois_tres++;
}

void main()
{
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1|RTCC_8_bit);        //51,2 us overflow


    enable_interrupts(INT_RTCC);
    enable_interrupts(GLOBAL);

    while(TRUE)
    {
        if(contador_um > a_cada_382_dividido_por_dois_overflow_pisca) {
            output_toggle(PIN_D5);
            contador_um = 0;
        }
        if(contador_dois_tres > a_cada_331_dividido_por_dois_overflow_pisca) {
            output_toggle(PIN_D6);
            output_toggle(PIN_D7);
            contador_dois_tres = 0;
        }
    }

}
