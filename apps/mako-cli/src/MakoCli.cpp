#include <iostream>
#include <cli.h>

int main() {
    mako::CliApplication cli = mako::CliApplication();
    return cli.run();
}