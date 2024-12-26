#include <stdio.h>
#include <string.h>

int crc(char *ip, char *op, char *poly, int mode) {
    strcpy(op, ip);
    if (mode) {
        for (int i = 1; i < strlen(poly); i++)
            strcat(op, "0");
    }

    // Perform XOR on the message with the selected polynomial
    for (int i = 0; i < strlen(ip); i++) {
        if (op[i] == '1') {
            for (int j = 0; j < strlen(poly); j++) {
                if (op[i + j] == poly[j])
                    op[i + j] = '0';
                else
                    op[i + j] = '1';
            }
        }
    }

    // Check for errors; return 0 if error detected
    for (int i = 0; i < strlen(op); i++) {
        if (op[i] == '1')
            return 0;
    }
    return 1;
}

int main() {
    char ip[50], op[100], recv[50];
    char poly[] = "10111";

    printf("Enter the input message in binary:\n");
    scanf("%s", ip);

    crc(ip, op, poly, 1);
    printf(op);
    printf("The transmitted message is: %s\n%s\n", ip, op + strlen(ip));

    printf("Enter the received message in binary:\n");
    scanf("%s", recv);

    if (crc(recv, op, poly, 0))
        printf("No error in data\n");
    else
        printf("Error in data transmission has occurred\n");

    return 0;
}
