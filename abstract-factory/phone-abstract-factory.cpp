#include <iostream>
#include <memory>
#include <vector>

// Smartphones class hierarchy
class ISmartphone {
 public:
  virtual ~ISmartphone() = default;
  virtual std::string getPhoneModel() const = 0;
};

class Samsung : public ISmartphone {};

class BudgetSamsung : public Samsung {
 public:
  std::string getPhoneModel() const override { return "Samsung Galaxy A20"; }
};

class PremiumSamsung : public Samsung {
 public:
  std::string getPhoneModel() const override {
    return "Samsung Galaxy S24 Ultra";
  }
};

class Apple : public ISmartphone {};

class BudgetApple : public Apple {
  std::string getPhoneModel() const override { return "Apple iPhone SE"; }
};

class PremiumApple : public Apple {
  std::string getPhoneModel() const override {
    return "Apple iPhone 15 Pro Max";
  }
};

// Factories class hierarchy
class IAbstractSmartphoneFactory {
 public:
  virtual ~IAbstractSmartphoneFactory() = default;
  virtual std::unique_ptr<ISmartphone> makeBudgetPhone() const = 0;
  virtual std::unique_ptr<ISmartphone> makePremiumPhone() const = 0;
};

class SamsungFactory : public IAbstractSmartphoneFactory {
 public:
  std::unique_ptr<ISmartphone> makeBudgetPhone() const override {
    return std::make_unique<BudgetSamsung>();
  }
  std::unique_ptr<ISmartphone> makePremiumPhone() const override {
    return std::make_unique<PremiumSamsung>();
  }
};

class AppleFactory : public IAbstractSmartphoneFactory {
 public:
  std::unique_ptr<ISmartphone> makeBudgetPhone() const override {
    return std::make_unique<BudgetApple>();
  }
  std::unique_ptr<ISmartphone> makePremiumPhone() const override {
    return std::make_unique<PremiumApple>();
  }
};

void createSomePhones(const IAbstractSmartphoneFactory& phoneFactory) {
  std::unique_ptr<ISmartphone> budgetPhone{phoneFactory.makeBudgetPhone()};
  std::unique_ptr<ISmartphone> premiumPhone{phoneFactory.makePremiumPhone()};
  std::cout << "Created budget phone: " << budgetPhone->getPhoneModel()
            << std::endl;
  std::cout << "Created premium phone: " << premiumPhone->getPhoneModel()
            << std::endl;
}

int main() {
  const SamsungFactory samsungFactory;
  const AppleFactory appleFactory;
  createSomePhones(samsungFactory);
  createSomePhones(appleFactory);
  return 0;
}