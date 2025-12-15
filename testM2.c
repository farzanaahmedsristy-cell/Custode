#include "manage.c"

int test_stock_out_valid()
{
    Item item;
    item.itemId = 1;
    strcpy(item.name, "Keyboard");
    item.quantity = 50;

    StockTransaction tx = {1001, 1, STOCK_OUT, 30};

    processStockTransaction(&item, &tx);

    int actual = item.quantity;
    int expected = 20;   // 50 - 30
    int success = actual == expected;

    printf("expected: %d, actual: %d, success: %d\n",
           expected, actual, success);

    return success;
}

int main()
{
    test_stock_out_valid();
    return 0;
}#include "manage.c"

int test_stock_out_valid()
{
    Item item;
    item.itemId = 1;
    strcpy(item.name, "Keyboard");
    item.quantity = 50;

    StockTransaction tx = {1001, 1, STOCK_OUT, 30};

    processStockTransaction(&item, &tx);

    int actual = item.quantity;
    int expected = 20;   // 50 - 30
    int success = actual == expected;

    printf("expected: %d, actual: %d, success: %d\n",
           expected, actual, success);

    return success;
}

int main()
{
    test_stock_out_valid();
    return 0;
}

