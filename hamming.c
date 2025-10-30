#include <stdio.h>

int main() {
    int d[4], h[7], p[3], err = 0;

    printf("Enter 4 data bits (D1 D2 D3 D4): ");
    for(int i=0;i<4;i++) scanf("%d",&d[i]);

    // Assign data bits
    h[2]=d[0]; h[4]=d[1]; h[5]=d[2]; h[6]=d[3];

    // Calculate parity bits (even parity)
    h[0]=h[2]^h[4]^h[6];  // P1
    h[1]=h[2]^h[5]^h[6];  // P2
    h[3]=h[4]^h[5]^h[6];  // P4

    printf("\nHamming Code: ");
    for(int i=0;i<7;i++) printf("%d ",h[i]);
    printf("\n");

    // Simulate error
    int pos;
    printf("Enter bit position to flip (0 for none): ");
    scanf("%d",&pos);
    if(pos>0 && pos<=7) h[pos-1]^=1;

    // Recalculate parity for error detection
    p[0]=h[0]^h[2]^h[4]^h[6];
    p[1]=h[1]^h[2]^h[5]^h[6];
    p[2]=h[3]^h[4]^h[5]^h[6];
    err = p[0] + p[1]*2 + p[2]*4;

    if(err==0) printf("No error detected.\n");
    else {
        printf("Error at bit position %d. Corrected.\n", err);
        h[err-1]^=1;
    }

    printf("Corrected Code: ");
    for(int i=0;i<7;i++) printf("%d ",h[i]);
    printf("\nData bits: %d %d %d %d\n", h[2], h[4], h[5], h[6]);
    return 0;
}
