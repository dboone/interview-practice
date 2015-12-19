#include <iostream>
#include <memory>

class BaseVirtual {
public:
    BaseVirtual() {
        std::cout << "BaseVirtual Constructor\n";
    }

    virtual ~BaseVirtual() {
        std::cout << "BaseVirtual Destructor\n";
    }
};

class DerivedVirtual : public BaseVirtual {
public:
    DerivedVirtual() {
        std::cout << "DerivedVirtual Constructor\n";
    }

    ~DerivedVirtual() {
        std::cout << "DerivedVirtual Destructor\n";
    }
};

class BaseNonVirtual {
public:
    BaseNonVirtual() {
        std::cout << "BaseNonVirtual Constructor\n";
    }

    ~BaseNonVirtual() {
        std::cout << "BaseNonVirtual Destructor\n";
    }
};

class DerivedNonVirtual : public BaseNonVirtual {
public:
    DerivedNonVirtual() {
        std::cout << "DerivedNonVirtual Constructor\n";
    }

    ~DerivedNonVirtual() {
        std::cout << "DerivedNonVirtual Destructor\n";
    }
};

class BaseProtected {
public:
    BaseProtected() {
        std::cout << "BaseProtected Constructor\n";
    }

protected:
    ~BaseProtected() {
        std::cout << "BaseProtected Destructor\n";
    }
};

class DerivedProtected : public BaseProtected {
public:
    DerivedProtected() {
        std::cout << "DerivedProtected Constructor\n";
    }

    ~DerivedProtected() {
        std::cout << "DerivedProtected Destructor\n";
    }
};

int main(int argc, char* argv[]) {
    // The well formed example with a virtual destructor
    // 1. Base Constructor
    // 2. Derived Constructor
    // 3. Derived Destructor
    // 4. Base Destructor
    {
        std::cout << "Well formed:\n";
        std::unique_ptr<BaseVirtual> p = std::make_unique<DerivedVirtual>();
    } std::cout << std::endl;

    // The not so well formed example
    // Lack of virtual destructor is undefined behavior
    // 1. Base Constructor
    // 2. Derived Constructor
    // 3. Base Destructor
    {
        std::cout << "Undefined behavior:\n";
        std::unique_ptr<BaseNonVirtual> p = std::make_unique<DerivedNonVirtual>();
    } std::cout << std::endl;

    // Protected destructor
    // Does not require virtual
    // 1. Base Constructor
    // 2. Derived Constructor
    // 3. Derived Destructor
    // 4. Base Destructor
    {
        std::cout << "Protected:\n";
        // Compile error! Cannot access protected member ~BaseProtected()
        //std::unique_ptr<BaseProtected> p = std::make_unique<BaseProtected>();

        // Compile error! Cannot access protected member ~BaseProtected()
        //std::unique_ptr<BaseProtected> p = std::make_unique<DerivedProtected>();

        // Non-polymorphic usage OK
        // Does not require virtual, derived type has access to protected member
        std::unique_ptr<DerivedProtected> p = std::make_unique<DerivedProtected>();
    } std::cout << std::endl;
    return 0;
}