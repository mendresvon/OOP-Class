class Product {
private:
    double price;   // cannot be set directly from outside
 
public:
    void setPrice(double p) {
        if (p >= 0) price = p;   // validation enforced here
    }
    double getPrice() const {
        return price;
    }
};
 
int main() {
    Product item;
    item.setPrice(29.99);       // ✅ valid
    item.setPrice(-5.0);        // silently rejected
    // item.price = -5.0;       // ❌ compile error — private
    return 0;
}

