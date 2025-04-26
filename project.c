#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 50


typedef struct {
    int id;
    char name[30];
    float price;
} MenuItem;

// Structure to define an order item
typedef struct {
    MenuItem item;
    int quantity;
} OrderItem;

// Menu items
MenuItem menu[] = {
    {1, "Burger", 150.0},
    {2, "Pizza", 300.0},
    {3, "Fries", 100.0},
    {4, "Soda", 50.0},
    {5, "Pasta", 250.0}
};
int menuSize = sizeof(menu) / sizeof(menu[0]);

OrderItem cart[MAX_ITEMS];
int cartSize = 0;

// Function declarations
void showMenu();
void addToCart();
void viewCart();
void checkout();
void processMpesaPayment();
void processPayPalPayment();
void processCashOnDelivery();
void processCardPayment();
float calculateTotal();

int main() {
    int choice;
    int menuViewed = 0; // Flag to track if the menu has been viewed

    printf(" Welcome to BYJU'S Food Order System \n");
    do {
        printf("SELECTION MENU \n");
        if (!menuViewed) {
            printf("1. View Menu\n");
        }
        printf("2. Add Item to Cart\n");
        printf("3. View Cart\n");
        printf("4. Checkout\n");
        printf("5. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (menuViewed && choice == 1) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        switch (choice) {
            case 1:
                if (!menuViewed) {
                    showMenu();
                    menuViewed = 1; // Mark menu as viewed
                }
                break;
            case 2:
                addToCart();
                break;
            case 3:
                viewCart();
                break;
            case 4:
                checkout();
                break;
            case 5:
                printf("Thank you for visiting!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to display menu
void showMenu() {
    printf("FOOD MENU\n");
    for (int i = 0; i < menuSize; i++) {
        printf("%d. %s - Ksh %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("\n");
}

// Function to add item(s) to cart
void addToCart() {
    char more;
    do {
        int itemId, quantity;
        showMenu();
        printf("Enter the item ID to add to cart (or 0 to go back): ");
        scanf("%d", &itemId);

        if (itemId == 0) {
            return; // Go back to the previous menu
        }

        int found = 0;
        for (int i = 0; i < menuSize; i++) {
            if (menu[i].id == itemId) {
                printf("Enter quantity for %s: ", menu[i].name);
                scanf("%d", &quantity);

                cart[cartSize].item = menu[i];
                cart[cartSize].quantity = quantity;
                cartSize++;

                printf("%s x%d added to cart.\n", menu[i].name, quantity);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid item ID. Please try again.\n");
        }

        printf("Do you want to add another item? (y/n): ");
        scanf(" %c", &more);
    } while (more == 'y' || more == 'Y');
}

// Function to view cart
void viewCart() {
    if (cartSize == 0) {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf(" YOUR CART \n");
    float total = 0;
    for (int i = 0; i < cartSize; i++) {
        float itemTotal = cart[i].item.price * cart[i].quantity;
        printf("%s x%d - Ksh %.2f\n", cart[i].item.name, cart[i].quantity, itemTotal);
        total += itemTotal;
    }
    printf("Total: Ksh %.2f\n", total);
    printf("\n");
}

// Function to handle checkout and payment options
void checkout() {
    viewCart();
    if (cartSize == 0) return;

    printf("\nProceeding to checkout...\n");
    printf("Generating final bill...\n");

    // Display total amount
    printf("Total: Ksh %.2f\n", calculateTotal());

    // Select payment method
    int paymentChoice;
    do {
        printf("PAYMENT OPTIONS\n");
        printf("1. Mpesa\n");
        printf("2. PayPal\n");
        printf("3. Cash on Delivery\n");
        printf("4. Credit/Debit Card\n");
        printf("5. Go Back\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &paymentChoice);

        switch (paymentChoice) {
            case 1:
                processMpesaPayment();
                printf("\nThank you for your payment! We hope to see you again soon.\n");
                exit(0); // Exit after payment
            case 2:
                processPayPalPayment();
                printf("\nThank you for your payment! We hope to see you again soon.\n");
                exit(0); // Exit after payment
            case 3:
                processCashOnDelivery();
                printf("\nThank you for your payment! We hope to see you again soon.\n");
                exit(0); // Exit after payment
            case 4:
                processCardPayment();
                printf("\nThank you for your payment! We hope to see you again soon.\n");
                exit(0); // Exit after payment
            case 5:
                return; // Go back to the previous menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (paymentChoice != 5);
}

// Function to handle Mpesa payment
void processMpesaPayment() {
    printf("\nMpesa Payment Selected.\n");
    printf("To pay, send Ksh %.2f to Paybill Number: 123456, Account: FoodOrder.\n", calculateTotal());
    printf("You will receive a confirmation SMS once payment is successful.\n");
}

// Function to handle PayPal payment
void processPayPalPayment() {
    printf("\nPayPal Payment Selected.\n");
    printf("Redirecting to PayPal...\n");
    printf("Please log in to your PayPal account to complete the payment of Ksh %.2f.\n", calculateTotal());
}

// Function to handle Cash on Delivery payment
void processCashOnDelivery() {
    printf("\nCash on Delivery Selected.\n");
    printf("You will pay the amount of Ksh %.2f upon delivery of your order.\n", calculateTotal());
}

// Function to handle Credit/Debit Card payment
void processCardPayment() {
    printf("\nCard Payment Selected.\n");
    printf("Please enter your card details to complete the payment of Ksh %.2f.\n", calculateTotal());
    printf("Card Number: ");
    char cardNumber[20];
    scanf("%s", cardNumber);
    printf("Expiry Date: ");
    char expiryDate[10];
    scanf("%s", expiryDate);
    printf("CVV: ");
    char cvv[5];
    scanf("%s", cvv);
    printf("Processing payment...\n");
    printf("Payment successful. Thank you!\n");
}

// Function to calculate the total price
float calculateTotal() {
    float total = 0;
    for (int i = 0; i < cartSize; i++) {
        total += cart[i].item.price * cart[i].quantity;
    }
    return total;
}
