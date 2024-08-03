#include <stdint.h>
#include <avr/io.h>

#include "matrix.h"
#include "wait.h"

// Matrix selector connects to two cascaded 74HC138s, which are directly driven.
#define MATRIX_PORT PORTB
#define MATRIX_DDR  DDRB
#define MATRIX_SELECT_A (1<<0)
#define MATRIX_SELECT_B (1<<1)
#define MATRIX_SELECT_C (1<<2)
#define MATRIX_SELECT_P138SEL (1<<3)
#define MATRIX_MASK (MATRIX_SELECT_A | MATRIX_SELECT_B | MATRIX_SELECT_C | MATRIX_SELECT_P138SEL)

#define INPUT_PIN  PINA
#define INPUT_PORT PORTA
#define INPUT_DDR  DDRA
#define INPUT_MASK (0xFF)

static void ports_init(void) {
    // Set up input: port C7 and all of port B
    // we want to enable internal pull-ups on all of these pins - the multiplexer (or whatever else in the case of 5 and 6)
    // will pull its selected line low, and therefore if we test low, selected key is pressed, high, key is not pressed.
    INPUT_DDR  &= ~INPUT_MASK;
    INPUT_PORT |=  INPUT_MASK;

    // Set up matrix selector output. These are driven directly, so DDR=1, toggle PORT
    MATRIX_PORT &= ~MATRIX_MASK;
    MATRIX_DDR  |=  MATRIX_MASK; // start as output-low}
}

static void matrix_select_row(uint8_t matrix_row){
    // Select output using four bits starting at MATRIX_SELECT_A
    // set output with MATRIX_PORT: 1 means high, 0 means low

    uint8_t output_port_val = 0; // start with all low level
    if(matrix_row & 0x1){
        output_port_val |= MATRIX_SELECT_A; // set DDR bit 0 for high level
    }
    if(matrix_row & 0x2){
        output_port_val |= MATRIX_SELECT_B;
    }
    if(matrix_row & 0x4){
        output_port_val |= MATRIX_SELECT_C;
    }
    if(matrix_row & 0x8){
        output_port_val |= MATRIX_SELECT_P138SEL;
    }

    MATRIX_PORT = (MATRIX_PORT & ~MATRIX_MASK) | output_port_val;

    // Give some time to settle. Without this the y key produces "y6"
    // and the 5 key produces "5t". Empirically >= 2us is sufficient,
    // so let's add a slightly larger tolerance.
    wait_us(5);
}

static uint8_t matrix_read_column(uint8_t matrix_column){
    uint8_t val = (INPUT_PIN & (1 << matrix_column)) == 0;
    return val;
}

void matrix_init_custom(void) {
    ports_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_select_row(row);

        matrix_row_t next = 0;
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            next |= MATRIX_ROW_SHIFTER << matrix_read_column(col);
        }

        matrix_row_t current = current_matrix[row];
        current_matrix[row] = next;
        matrix_has_changed |= current != next;
    }

    return matrix_has_changed;
}
