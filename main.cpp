#include <iostream>

#include "ui.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    UI* ui = new UI();

    delete ui;

    return 0;
}
