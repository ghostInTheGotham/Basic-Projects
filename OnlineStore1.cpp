#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <map>
#include <fstream>

using namespace std;

struct Product {
    int productID;
    string name;
    string category;
};

struct Order {
    int orderID;
    int productID;
    int quantity;
    string customerID;
    time_t orderDate;
};

/* ---------- Global Data ---------- */
vector<Product> products = {
    {101,"Laptop","Electronics"},
    {102,"Smartphone","Electronics"},
    {103,"Coffee Maker","Kitchen"},
    {104,"Blender","Kitchen"},
    {105,"Desk Lamp","Home"},
};

map<int,int> productStock = {
    {101,10},{102,20},{103,15},{104,5},{105,7}
};

unordered_map<string,string> customerData = {
    {"C001","Nikhil"},
    {"C002","Satyam"},
    {"C003","Pratyush"},
    {"C004","Abhinav"},
    {"C005","Rahul"}
};

list<Order> orderHistory;
multimap<string,Order> customerOrders;
deque<string> recentCustomers;

int nextOrderID = 1;

/* ---------- File Handling ---------- */

void loadOrdersFromFile() {
    ifstream file("orders.txt");
    if (!file) return;

    Order o;
    while (file >> o.orderID >> o.productID >> o.quantity >> o.customerID >> o.orderDate) {
        orderHistory.push_back(o);
        customerOrders.insert({o.customerID, o});
        nextOrderID = max(nextOrderID, o.orderID + 1);
    }
    file.close();
}

void saveOrderToFile(const Order& o) {
    ofstream file;
    file.open("orders.txt", ios::out | ios::app);

    if (!file) {
        cout << "Error creating file!\n";
        return;
    }

    file << o.orderID << " "
         << o.productID << " "
         << o.quantity << " "
         << o.customerID << " "
         << o.orderDate << endl;

    file.close();
}


/* ---------- Admin Login ---------- */

bool adminLogin() {
    string user, pass;
    cout << "\nAdmin Username: ";
    cin >> user;
    cout << "Admin Password: ";
    cin >> pass;

    return (user == "admin" && pass == "admin123");
}

/* ---------- Functions ---------- */

void showProducts() {
    cout << "\n--- Available Products ---\n";
    for (const auto& p : products) {
        cout << p.productID << " | " << p.name
             << " | " << p.category
             << " | Stock: " << productStock[p.productID] << endl;
    }
}

void placeOrder() {
    string customerID;
    int productID, quantity;

    cout << "\nEnter Customer ID: ";
    cin >> customerID;

    if (customerData.find(customerID) == customerData.end()) {
        cout << "❌ Customer not found!\n";
        return;
    }

    cout << "Enter Product ID: ";
    cin >> productID;

    if (productStock.find(productID) == productStock.end()) {
        cout << "❌ Product not found!\n";
        return;
    }

    cout << "Enter Quantity: ";
    cin >> quantity;

    if (productStock[productID] < quantity) {
        cout << "❌ Insufficient stock!\n";
        return;
    }

    Order newOrder = {
        nextOrderID++,
        productID,
        quantity,
        customerID,
        time(0)
    };

    orderHistory.push_back(newOrder);
    customerOrders.insert({customerID, newOrder});
    productStock[productID] -= quantity;

    recentCustomers.push_front(customerID);
    if (recentCustomers.size() > 5)
        recentCustomers.pop_back();

    saveOrderToFile(newOrder);

    cout << "✅ Order placed & saved successfully!\n";
}

void viewOrderHistory() {
    cout << "\n--- Order History ---\n";
    for (const auto& o : orderHistory) {
        cout << "OrderID: " << o.orderID
             << ", ProductID: " << o.productID
             << ", Qty: " << o.quantity
             << ", Customer: " << o.customerID << endl;
    }
}

void adminPanel() {
    if (!adminLogin()) {
        cout << "❌ Access Denied!\n";
        return;
    }

    cout << "\n🔐 Welcome Admin\n";
    cout << "\n--- Product Stock ---\n";
    for (const auto& s : productStock)
        cout << "Product " << s.first << " => " << s.second << endl;

    viewOrderHistory();
}

/* ---------- Main ---------- */

int main() {
    loadOrdersFromFile();

    int choice;
    do {
        cout << "\n==============================\n";
        cout << " Mini E-Commerce System\n";
        cout << "==============================\n";
        cout << "1. View Products\n";
        cout << "2. Place Order\n";
        cout << "3. Admin Panel\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showProducts(); break;
            case 2: placeOrder(); break;
            case 3: adminPanel(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "❌ Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
// Admin Credentials
// Username: admin
// Password: 1234
 
