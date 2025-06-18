#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>
#include <type_traits>

template<typename T>
using ComplexT = std::complex<T>;

template<typename T>
struct RootInfo {
    ComplexT<T> value;
    bool converged;
    int iterations;
};

template<typename T>
struct Polynomial {
    std::vector<ComplexT<T>> coeffs; // от старшей к младшей степени

    Polynomial(const std::vector<ComplexT<T>>& c) : coeffs(c) {}

    // Оценка значения многочлена в точке x
    ComplexT<T> eval(const ComplexT<T>& x) const {
        ComplexT<T> result = coeffs[0];
        for (size_t i = 1; i < coeffs.size(); ++i)
            result = result * x + coeffs[i];
        return result;
    }

    // Вычисление производной
    Polynomial<T> derivative() const {
        std::vector<ComplexT<T>> deriv;
        int n = coeffs.size() - 1;
        for (int i = 0; i < n; ++i)
            deriv.push_back(coeffs[i] * ComplexT<T>(n - i, 0));
        return Polynomial<T>(deriv);
    }

    // Дефляция (деление на (x - root))
    Polynomial<T> deflate(const ComplexT<T>& root) const {
        int n = coeffs.size() - 1;
        std::vector<ComplexT<T>> new_coeffs(n);
        new_coeffs[0] = coeffs[0];
        for (int i = 1; i < n; ++i)
            new_coeffs[i] = coeffs[i] + new_coeffs[i - 1] * root;
        return Polynomial<T>(new_coeffs);
    }
};

// Генерация начального приближения (по кругу)
template<typename T>
ComplexT<T> initial_guess(int degree, int idx) {
    T angle = 2 * M_PI * idx / degree;
    return ComplexT<T>(std::cos(angle), std::sin(angle));
}

// Поиск одного корня методом Ньютона с контролем сходимости
template<typename T>
RootInfo<T> find_root_newton(const Polynomial<T>& poly, const ComplexT<T>& start, T eps = 1e-12, int max_iter = 1000) {
    Polynomial<T> deriv = poly.derivative();
    ComplexT<T> z = start;
    bool converged = false;
    int iter = 0;
    for (; iter < max_iter; ++iter) {
        ComplexT<T> fz = poly.eval(z);
        if (std::abs(fz) < eps) {
            converged = true;
            break;
        }
        ComplexT<T> dfz = deriv.eval(z);
        if (std::abs(dfz) < eps) break;
        z = z - fz / dfz;
    }
    return {z, converged, iter};
}

// Основная функция поиска всех корней
template<typename T>
std::vector<RootInfo<T>> find_all_roots(const Polynomial<T>& poly, T eps = 1e-12, int max_iter = 1000) {
    std::vector<RootInfo<T>> roots;
    Polynomial<T> current = poly;
    int degree = current.coeffs.size() - 1;
    for (int i = 0; i < degree; ++i) {
        ComplexT<T> guess = initial_guess<T>(degree, i) * T(0.5) + ComplexT<T>(0.5, 0.5);
        RootInfo<T> info = find_root_newton<T>(current, guess, eps, max_iter);
        roots.push_back(info);
        current = current.deflate(info.value);
    }
    return roots;
}

// Пример использования с вводом с клавиатуры
int main() {
    using T = double;
    int degree;
    std::cout << "Введите степень многочлена (например, 3): ";
    std::cin >> degree;
    if (degree < 1) {
        std::cout << "Степень должна быть >= 1\n";
        return 1;
    }
    std::vector<ComplexT<T>> coeffs(degree + 1);
    std::cout << "Введите коэффициенты (действительная и мнимая часть через пробел) от старшей степени к младшей:\n";
    for (int i = 0; i <= degree; ++i) {
        double re, im;
        std::cout << "Коэффициент при x^" << (degree - i) << ": ";
        std::cin >> re >> im;
        coeffs[i] = ComplexT<T>(re, im);
    }
    Polynomial<T> poly(coeffs);

    auto roots = find_all_roots<T>(poly);

    std::cout << "Roots found:\n";
    for (const auto& r : roots) {
        std::cout << "Root: " << r.value << " | Converged: " << (r.converged ? "yes" : "no")
                  << " | Iterations: " << r.iterations << "\n";
    }
    return 0;
}