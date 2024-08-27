#include <fcgi_stdio.h>

int main(void) {
    while (FCGI_Accept() >= 0) {
        printf("Content-type: text/html\n\n");
        printf("<html><body><h1>Hello World!</h1></body></html>");
    }
    return 0;
}
