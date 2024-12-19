#include <stdio.h>
#include <stdarg.h>

void print_numbers(int count, ...) {
    va_list args;  // Yeh ek bag hai jisme tumhare extra cheezein rakhi jayengi.
    
    va_start(args, count);  // Bag ko open karte ho aur cheezein daal dete ho.
    
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);  // Bag se ek ek cheez nikaalte ho.
        printf("%d\n", num);  // Cheez ko print karte ho.
    }

    va_end(args);  // Bag ko band kar dete ho.
}

int main() {
    print_numbers(3, 10, 20, 30);  // Tum 3 numbers pass kar rahe ho.
    return 0;
}
