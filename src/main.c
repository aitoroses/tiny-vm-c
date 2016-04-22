#include <stdbool.h>
#include <stdio.h>

int* program;

// VM Implementation
typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    PRINT,
    MOV,
    HLT
} InstructionSet;

typedef enum {  
   A, B, C, D, E, F, PC, SP,
   NUM_OF_REGISTERS
} Registers;

#define sp (registers[SP])
#define ip (registers[PC])

int stack[256];
int registers[NUM_OF_REGISTERS];  
bool running = true;

int fetch() {
    return *( program + ip);
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = *( program + ++ip );
            break;
        }
        case POP: {
            registers[program[++ip]] = stack[sp];
            stack[sp] = 0;
            sp--;
            break;
        }
        case ADD: {
            int a = stack[sp];
            stack[sp--] = 0;
            int b = stack[sp];
            stack[sp--] = 0;
            int result = b + a;
            sp++;
            stack[sp] = result;
            break;
        }
        case SET: {
            int registr = program[++ip];
            int value = program[++ip];
            registers[registr] = value;
            ip--;
            break;
        }
        case PRINT: {
            printf("%d\n", registers[program[++ip]]);
            break;
        }
    }
}

void printStatus() {
    // Print program status
    printf("\nPC: %d, SP: %d \n", registers[PC], registers[SP]);
    
    printf("A: %d, B: %d ", registers[A], registers[B]);
    printf("C: %d, D: %d ", registers[C], registers[D]);
    printf("E: %d, F: %d\n", registers[E], registers[F]);
    
    printf("STACK: ");
    for (int i = 0; i < 256; i++) {
        printf("%d ", stack[i]);
    }
    
    printf("\n\n");
}

void run(int prog[]) {
    sp = -1;
    ip = 0;
    program = prog;
    while (running) {
        eval(fetch());
        ip++;     
        printStatus();
    }
}

// Running code

int main() {
    
    // Program
    int program[] = {
        PSH, 5,
        PSH, 6,
        ADD,
        POP, A,
        PRINT, A,
        HLT
    };
    
    run(program);
    
    return 0;

}
