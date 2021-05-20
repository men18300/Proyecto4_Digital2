//Universidad del Valle de Guatemala
//Depto de Ingenieria Mecantronica y Electronica
//Curso Digital2
//Prof. Kurt Kellner
//Diego Mencos
//Carne 18300

//Proyecto 4

//Bibliotecas
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"


//Variables a usar en el programa
int status1=1;
int status2=1;
int status3=1;
int status4=1;

int status1prev=1;
int status2prev=1;
int status3prev=1;
int status4prev=1;

int contador=0;
int parqueo1=0;
int parqueo2=0;
int parqueo3=0;
int parqueo4=0;


//Prototipo de funciones
void UARTIntHandler(void); //funcion interrupcion cuando se recibe un dato por UART
void InitUART(void); //funcion de configuracion UART
void InitUART1(void);
void InitUART2(void);
void LEDsparqueo(void);
void delayMs(uint32_t ui32Ms);


//Main Loop
int main(void) {
    //Establecer reloj del microcontrolador a 40
    SysCtlClockSet(SYSCTL_SYSDIV_5| SYSCTL_USE_PLL| SYSCTL_XTAL_16MHZ);

    //Funcion de configuracion de UART0
    InitUART1();

    //Habilitar periférico GPIO F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Habilitar pines de salida y entrada

    //Habilitar periférico GPIO C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //Habilitar pines de salida y entrada
    //Habilitar periférico GPIO C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //Habilitar pines de salida y entrada

    GPIOPinConfigure(GPIO_PD6_WT5CCP0);
    GPIOPinConfigure(GPIO_PC7_WT1CCP1);


    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    //Configura los pushbuttoms con weak pull-up

  //  GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);
    //Configura los pushbuttoms con weak pull-up

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //IntEnable(INT_UART2);
    //IntMasterEnable();



    //loop infinito
    while (1){
                //funcion de toggle del led
        status3 = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6);
        status1 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        status2 = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7);


        if (status1prev!=status1){
            status1prev=status1;
            if (status1==0){
                        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8); //Rojo
                        UARTCharPut(UART1_BASE, 'a');
                        //delayMs(1000);
                    }
                        else {
                            UARTCharPut(UART1_BASE, 'b');
                          //  delayMs(500);
                        }
        }


        if (status2prev!=status2){
            status2prev=status2;
            if (status2==0){
          GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6); //Rojo
          UARTCharPut(UART1_BASE, 'c');
          //delayMs(1000);
      }
      else {
          UARTCharPut(UART1_BASE, 'd');
         // delayMs(500);
      }

        }

        if (status3prev!=status3){
            status3prev=status3;
            if (status3==0){
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10); //amarillo
                UARTCharPut(UART1_BASE, 'e');
             // delayMs(1000);
           }
            else if (status3==1){
                UARTCharPut(UART1_BASE, 'f');
               // delayMs(500);
            }


        }


            else{
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); //Rojo
            }

    }
}


void InitUART(void){
    /*Enable the GPIO Port A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /*Enable the peripheral UART Module 0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Make the UART pins be peripheral controlled. */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Sets the configuration of a UART. */
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Habilitamos las interrupciones de UART
  //  UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //LLamamos a la funcion de interrupcion
  //  UARTIntRegister(UART0_BASE ,UARTIntHandler);
}

void InitUART1(void){
    /*Enable the GPIO Port A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    /*Enable the peripheral UART Module 0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    //Establecemos los pines RX/C4 y TX/C5
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinConfigure(GPIO_PC4_U1RX);

    /* Make the UART pins be peripheral controlled. */
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);


    /* Sets the configuration of a UART. */
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

  //  UARTEnable(UART1_BASE);
   // UARTFIFOEnable(UART1_BASE);

    //Habilitamos las interrupciones de UART
   // UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    //LLamamos a la funcion de interrupcion
   // UARTIntRegister(UART1_BASE ,UARTIntHandler);
}


void InitUART2(void){
    /*Enable the GPIO Port A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    /*Enable the peripheral UART Module 0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);

    /* Make the UART pins be peripheral controlled. */
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    /* Sets the configuration of a UART. */
    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Habilitamos las interrupciones de UART
   // UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    //LLamamos a la funcion de interrupcion
   // UARTIntRegister(UART1_BASE ,UARTIntHandler);
}




//Interrupcion cuando se recibe un dato, guardamos en una variable el valor y cambiamos el color
void UARTIntHandler(){
    UARTIntClear (UART1_BASE, UART_INT_RX|UART_INT_TX);
    //UARTCharPut(UART0_BASE, 'r');

}


void LEDsparqueo(void){
    if(parqueo1== 1 ){


    }
    else if (parqueo1==0){


    }
    if(parqueo2==1){

    }
    else if (parqueo2==0){

    }
    if(parqueo3==1){

    }
    else if (parqueo3==0){

    }
    if(parqueo4==1){

    }
    else if (parqueo4==0){

    }

    contador=parqueo1+parqueo2+parqueo3+parqueo4;
    if (contador==0){}
    else if (contador==2){}
    else if (contador==3){}
    else if (contador==4){}
    else {}
}


//Este delay sirve para poder utilizar el delay que traen las librerias pero con un
//valor exacto en ms
void delayMs(uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}




