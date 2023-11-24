// Include standard input-output and other necessary headers.
#include <iostream>
#include "wrap.h"
#include "startup.h"
#include <stdlib.h>

// Define a type for 32-bit unsigned integers.
typedef unsigned int uint32_t;

// Define base address and register offsets for GPIO operations.
#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_INPUT_VAL 0x0

#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38

#define GPIO_PULLUP_EN 0x10

// Define GPIO pin numbers for LEDs and buttons.
#define GREEN_LED 18
#define RED_LED 3
#define YELLOW_LED 0
#define BLUE_LED 21

#define GREEN_BUTTON 19
#define RED_BUTTON 2
#define YELLOW_BUTTON 1
#define BLUE_BUTTON 20

// Define constants for game logic and timings.
#define GreenLedNumber 1
#define RedLedNumber 0
#define YellowLedNumber 2
#define BlueLedNumber 3


const static uint32_t T_SHORT = 1500000u;
const static uint32_t  T_LONG =  2u * T_SHORT;
const static uint32_t  T_VERY_LONG = 2u * T_LONG;

#define TRUE 1
#define FALSE 0


#define Startlevel 1
#define AddTwo 2
#define LevelPlusOne 1
#define MAX_NODES 100
// Global variable for game level.
static int level = Startlevel;



// Structure for a node in a linked list.

typedef struct ListNode{

    int data;
    struct ListNode *next;

} ListNode;


// Global variables for managing linked list nodes.
static int nextFreeIndex = 0;
static ListNode nodeList[MAX_NODES];

// Functions for controlling LEDs and buttons.
void aktivLed(uint32_t object_led);
static void startLED(void);
void aktivButton(uint32_t object_button);
static void aktivButton(void);
void aktivEinzelLED(uint32_t object_led);
void deaktiviereEinzelLED(uint32_t object_led);
int istTastegedrueckt(uint32_t object_Button);
void deaktivierenAlleLED(void);
void blinkenAllLED(uint32_t time);
void blinkenLED(uint32_t object_LED, uint32_t time, uint32_t delay);
void blinkenZweiLED(uint32_t object_LED, uint32_t object_LED_TWO, uint32_t time, uint32_t delay);
// Functions implementing the game logic.
static void init(void);
static void bereitschaftsmodus_Sequenz(void);
static int zufallszahl(void);
static int zeitVerringern(void);
static ListNode *addNode(ListNode *head, int newData);
static void freeList(ListNode *head);
static void vorfuehrphaseAnfangSequenz(void);
static ListNode *vorfuehrphaseAnzeigen(void);
static ListNode *vorfuehrphase(void);
static void verlorensequenz(int level, int array[]);
static void ausgabeInBinaer(int level, int binaryArray[]);
static void zwischensequenz(void);
static void endeModus(void);
static void spielstarten(void);
static int doppeltEntfernen(void);
static int nachahmphaseEingabe(int value, uint32_t time);
static int nachahmphase(ListNode *head);


// Activate Object from the Redv-vp
//Param object:int Value from the Redv-vp Object
static ListNode *vorfuehrphase(void){
    vorfuehrphaseAnfangSequenz();
    ListNode *liste = vorfuehrphaseAnzeigen();
    blinkenAllLED(T_LONG);
    return liste;
}
struct ListNode static *addNode(struct ListNode *head, int data) {
    nextFreeIndex = nextFreeIndex+1;
    struct ListNode *newNode = &nodeList[nextFreeIndex];
    newNode->data = data;
    newNode->next = NULL;
    int controlReturn = TRUE;
    if (head == NULL) {
        controlReturn = FALSE;
    }
    struct ListNode *returnList = newNode;
    if (controlReturn == TRUE) {
        struct ListNode *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        returnList = head;
    }
    return returnList;
}
void freeList(struct ListNode *head) {
    struct ListNode *current = head;
    while (current != NULL) {
        const struct ListNode *temp = current;
        current = current->next;
        if (nextFreeIndex < (MAX_NODES - 1)) {
            nextFreeIndex = nextFreeIndex +1;
            nodeList[nextFreeIndex] = *temp;
        }
    }
}

void aktivLed(uint32_t object_led){
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << object_led);
    REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << object_led);
    REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1u << object_led;

}
static void startLED(void){
    aktivLed(GREEN_LED);
    aktivLed(BLUE_LED);
    aktivLed(YELLOW_LED);
    aktivLed(RED_LED);
}
void aktivButton(uint32_t object_button){
    REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << object_button);
    REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1u << object_button);
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << object_button);
    REG(GPIO_BASE + GPIO_INPUT_EN) |= 1u << object_button;
    REG(GPIO_BASE + GPIO_PULLUP_EN) |= 1u << object_button;

}
static void aktivButton(void){
    aktivButton(GREEN_BUTTON);
    aktivButton(BLUE_BUTTON);
    aktivButton(YELLOW_BUTTON);
    aktivButton(RED_BUTTON);
}
void aktivEinzelLED(uint32_t object_led){
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1u << object_led);
}
void deaktiviereEinzelLED(uint32_t object_led) {
    REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1u << object_led);
}
/**
 * Checks if a button is pressed
 * @param button that should be pressed
 * @return 0 when the button is not pressed and 1 when the button is pressed
*/
int istTastegedrueckt(uint32_t object_Button){
    int boolean = TRUE;

    if ((REG(GPIO_BASE + GPIO_INPUT_VAL) & (1u << object_Button))){
        boolean = FALSE;
    }else{
        boolean = TRUE;
    }
    return boolean;
}
/**
 * turns all leds on
*/
void blinkenAllLED(uint32_t time){
    aktivEinzelLED(GREEN_LED);
    aktivEinzelLED(BLUE_LED);
    aktivEinzelLED(YELLOW_LED);
    aktivEinzelLED(RED_LED);
    for (volatile uint32_t i = 0; i < time; i++){}
    deaktivierenAlleLED();
}
/**
 * turn all leds off
*/
void deaktivierenAlleLED(void){
    deaktiviereEinzelLED(GREEN_LED);
    deaktiviereEinzelLED(BLUE_LED);
    deaktiviereEinzelLED(YELLOW_LED);
    deaktiviereEinzelLED(RED_LED);
}

/**
 * turns a Led on
*/
void blinkenLED(uint32_t object_LED, uint32_t time, uint32_t delay) {
    aktivEinzelLED(object_LED);
    for (volatile uint32_t i = 0; i < time; i++) {}
    deaktiviereEinzelLED(object_LED);
    for (volatile uint32_t i = 0; i < delay; i++) {}
}
/**
 * turns Two leds on
*/
void blinkenZweiLED(uint32_t object_LED, uint32_t object_LED_TWO, uint32_t time, uint32_t delay){
    aktivEinzelLED(object_LED);
    aktivEinzelLED(object_LED_TWO);
    for (volatile uint32_t i = 0; i < time; i++){}
    deaktivierenAlleLED();
    for (volatile uint32_t i = 0; i < delay; i++){}
}
static void init(void){
    startLED();
    aktivButton();
}
static void bereitschaftsmodus_Sequenz(void){
    int control = TRUE;
    int run = TRUE;
    while (run == TRUE){
        if ((istTastegedrueckt(GREEN_BUTTON) == TRUE) && (control == TRUE)){
            control = FALSE;
            run = FALSE;
        }else{}
        if (run == TRUE){
            (blinkenLED(GREEN_LED, T_SHORT, T_SHORT));
        }else{}
        if ((istTastegedrueckt(GREEN_BUTTON) == TRUE) && (control == TRUE)){
            control = FALSE;
            run = FALSE;
        }else{}
        if (run == TRUE){
            (blinkenLED(BLUE_LED, T_SHORT, T_SHORT));
        }else{}
        if ((istTastegedrueckt(GREEN_BUTTON) == TRUE) && (control == TRUE)){
            control = FALSE;
            run = FALSE;
        }else{}
        if (run == TRUE){
            (blinkenLED(YELLOW_LED, T_SHORT, T_SHORT));
        }
        else{}
        if ((istTastegedrueckt(GREEN_BUTTON) == TRUE) && (control == TRUE)){
            control = FALSE;
            run = FALSE;
        }else{}
        if (run == TRUE){
            (blinkenLED(RED_LED, T_SHORT, T_SHORT));
        }else{}

    }
    deaktivierenAlleLED();
}
/**
 * Generate a random number
 * @return random number
*/
static int zufallszahl(void) {
    int zufallZahl = (rand() % (3 - 1 + 1)) + 1;
    return zufallZahl;
}
static int zeitVerringern(void){
    int reduziere;
    int zeit = T_VERY_LONG;
    reduziere = (level % 2u == 0) ? level * 10.0 : 0;
    int reduce = zeit - (int)(zeit * (reduziere / 100.0));
    return reduce;
}
static void vorfuehrphaseAnfangSequenz(void){
    blinkenZweiLED(BLUE_LED, YELLOW_LED, T_SHORT, T_SHORT);
    for (volatile uint32_t i = 0; i < T_SHORT; i++){}
    deaktivierenAlleLED();
}
static ListNode *vorfuehrphaseAnzeigen(void){
    uint32_t anzahl = level + AddTwo;
    ListNode *liste = NULL;
    int t = zeitVerringern();
    for (int i = 0; i < anzahl; i++){
        int randomLED = zufallszahl();
        if (randomLED == GreenLedNumber){
            blinkenLED(GREEN_LED,t, T_SHORT);
            liste = addNode(liste, GreenLedNumber);
        }else if (randomLED == RedLedNumber){
            blinkenLED(GREEN_LED,t,T_SHORT);
            liste = addNode(liste, RedLedNumber);
        }else if (randomLED == YellowLedNumber){
            blinkenLED(YELLOW_LED, t, T_SHORT);
            liste = addNode(liste, YellowLedNumber);
        }else if (randomLED == BlueLedNumber){
            blinkenLED(BLUE_LED, t, T_SHORT);
            liste = addNode(liste, BlueLedNumber);
        }else{}
    }
    return liste;
}
static void verlorensequenz(int level, int array[]){
    blinkenZweiLED(GREEN_LED, RED_LED, T_SHORT, T_SHORT);
    blinkenZweiLED(GREEN_LED, RED_LED, T_SHORT, T_SHORT);
    ausgabeInBinaer(level, array);
    deaktivierenAlleLED();
}
static void zwischensequenz(void){
    blinkenZweiLED(GREEN_LED, YELLOW_LED, T_SHORT, 0);
    blinkenZweiLED(BLUE_LED, RED_LED, T_SHORT, 0);
    blinkenZweiLED(GREEN_LED, YELLOW_LED, T_SHORT, 0);
    blinkenZweiLED(BLUE_LED, RED_LED, T_SHORT, 0);
    level = level + LevelPlusOne;
}
static int doppeltEntfernen(void){

    int anzahl = 0;
    int booleanWert = FALSE;

    if(istTastegedrueckt(GREEN_BUTTON) == TRUE){
        anzahl++;
    } if (istTastegedrueckt(BLUE_BUTTON) == TRUE){
        anzahl++;
    } if (istTastegedrueckt(YELLOW_BUTTON) == TRUE){
        anzahl++;
    } if (istTastegedrueckt(RED_BUTTON) == TRUE){
        anzahl++;
    }
    if (anzahl > 1){
        booleanWert = FALSE;
    }else{
        booleanWert = TRUE;
    }
    return booleanWert;
}
static int nachahmphase(ListNode *head){
    ListNode *current = head;
    int t = zeitVerringern();
    int booleanWert = FALSE;

    while (current != NULL){
        int currentData = current -> data;
        int temp = nachahmphaseEingabe(currentData,t);
        if (temp == FALSE){
            booleanWert = FALSE;
            break;
        }
        else {
            if (currentData == GreenLedNumber){
                blinkenLED(GREEN_LED, T_SHORT, 0);
            }else if (currentData == BlueLedNumber){
                blinkenLED(BLUE_LED, T_SHORT, 0);
            }else if (currentData == YellowLedNumber){
                blinkenLED(YELLOW_LED, T_SHORT, 0);
            }else if (currentData == RedLedNumber){
                blinkenLED(RED_LED, T_SHORT, 0);
            }else{}

            current = current -> next;
        }
        booleanWert = TRUE;

    }
    return booleanWert;
}

static int nachahmphaseEingabe(int value, uint32_t time){
    int control = TRUE;
    int booleanWert = FALSE;
    if (doppeltEntfernen() == FALSE){
        booleanWert = FALSE;
    }else{}
    for(uint32_t i = 0; i < time;i++){
        if ((istTastegedrueckt(GREEN_BUTTON) == TRUE) && (control == TRUE)){
            if (value == GreenLedNumber){
                booleanWert = TRUE;
                control = FALSE;
            }else{
                control = FALSE;
                booleanWert = FALSE;

            }
        }else if ((istTastegedrueckt(BLUE_BUTTON) == TRUE) && (control == TRUE)){
            if (value == BlueLedNumber){
                booleanWert = TRUE;
                control = FALSE;

            }else{
                control = FALSE;
                booleanWert = FALSE;
            }
        }else if ((istTastegedrueckt(YELLOW_BUTTON) == TRUE) && (control == TRUE)){
            if (value == YellowLedNumber){
                control = FALSE;
                booleanWert = TRUE;
            }else{
                control = FALSE;
                booleanWert =  FALSE;
            }
        }else if ((istTastegedrueckt(RED_BUTTON) == TRUE) && (control == TRUE)){
            if (value == RedLedNumber){
                booleanWert =  TRUE;
                control = FALSE;
            }else{
                booleanWert =  FALSE;
                control = FALSE;
            }
        }else{}
        if(control == FALSE){
            break;
        }
    }
    return booleanWert;
}
static void ausgabeInBinaer(int level, int binaryArray[]){
    if ((level >= 0) && (level <= 10)){
        uint32_t arraySize = 4;
        for (uint32_t i = arraySize; i > 0; i--) {
            int shiftAmount;
            shiftAmount = arraySize - 1 - i;
            binaryArray[i] = (level >> shiftAmount) & 1;
        }
        for (uint32_t i = 0; i < T_VERY_LONG; i++) {
            for (uint32_t j = 0; j < arraySize; j++) {
                if (binaryArray[j] == 1) {
                    aktivEinzelLED(j == 0 ? GREEN_LED : (j == 1 ? BLUE_LED : (j == 2 ? YELLOW_LED : RED_LED)));
                }
            }
        }
    }
}
static void endeModus(void){
    blinkenAllLED(T_SHORT);
    for (volatile uint32_t i = 0; i < T_LONG; i++){}
    blinkenAllLED(T_LONG);
    for (volatile uint32_t i = 0; i < T_LONG; i++){}
    blinkenAllLED(T_SHORT);
    for (volatile uint32_t i = 0; i < T_LONG; i++){}
    blinkenAllLED(T_LONG);
}
static void spielstarten(void){
    init();
    int array [4];
    int controll = FALSE;
    while(TRUE){
        if(!controll){
            bereitschaftsmodus_Sequenz();
        }
        if(level <= 10){

            ListNode *liste = vorfuehrphase();
            int result = nachahmphase(liste);
            if (result == TRUE){

                controll = TRUE;
                zwischensequenz();
            }else{

                controll = FALSE;
                verlorensequenz(level, array);
                level = Startlevel;
            }
            freeList(liste);
        }else{

            controll = FALSE;
            endeModus();
        }

    }
}
// The main function continuously runs the game.
int main (void) {
    while (TRUE) {
        // Start and run the game.
        spielstarten();
         }
}