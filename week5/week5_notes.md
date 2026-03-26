# Week 5 — Functions (函式)

> **Course:** 2026 Spring — Object-Oriented Programming (物件導向程式設計)

---

## 1. Function Declaration & Definition (函式宣言與定義)

### Declaration (宣告)

A **declaration** tells the compiler the function's name, return type, and parameters — but does *not* provide the body.

```cpp
int sum(int a, int b);   // declaration (prototype)
```

### Definition (定義)

A **definition** includes the full body of the function.

```cpp
int sum(int a, int b)     // definition
{
    return a + b;
}
```

### Essential Components (必要的資訊)

| Component | Description |
|---|---|
| **Return type** (傳回型別) | Specifies the type of value the function returns. Use `void` if there is no return value. From C++11 onward, you can use `auto` to let the compiler deduce the return type. From C++14 onward, `decltype(auto)` is also available. |
| **Function name** (函式名稱) | An identifier that begins with a letter or underscore. |
| **Parameter list** (參數列) | A comma-separated list of zero or more parameters enclosed in parentheses, specifying each parameter's type and optionally a local name used to access the value inside the function body. |
| **`constexpr`** (optional) | Indicates that the function's return value is a constant value that can be computed at **compile time**. |

---

## 2. Function Signature (函式簽章)

A function's **signature** consists of its name and the number/types of its parameters (but *not* the return type). The signature is what the compiler uses to distinguish between overloaded functions.

---

## 3. DRY — Don't Repeat Yourself

A core software engineering principle:

- **Avoid duplicating logic.** If the same code appears in multiple places, extract it into a function.
- Reduces bugs — a fix in one place applies everywhere.
- Makes code easier to read, maintain, and test.

---

## 4. ODR — One Definition Rule

The **One Definition Rule** in C++ states:

- Every function, variable, class, or template must have **exactly one definition** across the entire program (across all translation units).
- A function may be **declared** multiple times, but **defined** only once.
- Violating the ODR results in a **linker error** (e.g., "multiple definition of ...").
- **Exception:** `inline` functions and templates may be defined in multiple translation units as long as all definitions are identical.

---

## 5. `constexpr` Functions

- A `constexpr` function indicates that the return value is a **compile-time constant** when called with constant expressions.
- Enables the compiler to evaluate the result during compilation rather than at runtime.

```cpp
constexpr int square(int x)
{
    return x * x;
}

int arr[square(5)];  // OK — evaluated at compile time, arr has 25 elements
```

---

## 6. Function Overloading (函式多載)

C++ allows multiple functions with the **same name** but **different parameter lists** (different signatures).

```cpp
// Example 1: Overloaded functions
int    add(int a, int b)       { return a + b; }
double add(double a, double b) { return a + b; }
```

```cpp
// Example 2: Different number of parameters
void print(int x)           { std::cout << x; }
void print(int x, int y)    { std::cout << x << ", " << y; }
```

The compiler selects the correct version based on the arguments provided at the call site.

---

## 7. Name Mangling (名稱修飾)

- **Name mangling** is the mechanism by which the C++ compiler encodes function names along with their parameter types to produce unique symbol names.
- This is what makes **function overloading** possible — even though two functions share the same source-level name, the mangled names are different.
- Example: `add(int, int)` might be mangled to `_Z3addii`, while `add(double, double)` becomes `_Z3adddd`.
- Name mangling is **compiler-specific** (GCC, MSVC, Clang each have their own schemes).
- Use `extern "C"` to disable name mangling when interfacing with C code.

---

## 8. Inline Functions (Inline 函式)

- The `inline` keyword suggests to the compiler that it should **replace the function call with the function body** at the call site, avoiding function-call overhead.
- Best for small, frequently called functions.
- `inline` functions are exempt from the ODR across translation units (as long as all definitions are identical).

```cpp
inline int max(int a, int b)
{
    return (a > b) ? a : b;
}
```

---

## 9. Operator Overloading (運算子多載)

- C++ allows you to **redefine the behavior of operators** (e.g., `+`, `-`, `<<`) for user-defined types (classes/structs).
- This is a form of function overloading — operators are essentially functions with special syntax.

```cpp
struct Point {
    int x, y;
    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};
```

---

## 10. Arrays (陣列)

- A fixed-size collection of elements of the same type, stored in contiguous memory.

```cpp
int scores[5] = {90, 85, 78, 92, 88};
```

---

## Key Takeaways

| Concept | One-Liner |
|---|---|
| **DRY** | Don't duplicate code — use functions. |
| **ODR** | One definition per entity across the entire program. |
| **constexpr** | Compute values at compile time. |
| **Name mangling** | Compiler encodes function signatures into unique symbols for overloading. |
| **Overloading** | Same function name, different parameter lists. |
| **Inline** | Hint to replace call with body to reduce overhead. |
| **Operator overloading** | Redefine operators for custom types. |
