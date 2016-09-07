#ifndef SUNDEW_CPP_BACKPORT_H
#define SUNDEW_CPP_BACKPORT_H

#if ! SUNDEW_COMPILER_SUPPORTS_OVERRIDE_AND_FINAL
    #undef override
    #define override

    #undef final
    #define final
#endif //SUNDEW_COMPILER_SUPPORTS_OVERRIDE_AND_FINAL

#if ! SUNDEW_COMPILER_SUPPORTS_NOEXCEPT
    #undef noexcept
    #define noexcept
#endif //SUNDEW_COMPILER_SUPPORTS_NOEXCEPT

#if ! SUNDEW_COMPILER_SUPPORTS_INTEGRAL_CONSTANT
    template<class Type, Type value>
    struct integral_constant
    {
        static const Type value = value;

        typedef Type value_type;
        typedef integral_constant type;

        operator value_type() const noexcept      { return value; }
        value_type operator()() const noexcept    { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
#endif //SUNDEW_COMPILER_SUPPORTS_INTEGRAL_CONSTANT

#if ! SUNDEW_COMPILER_SUPPORTS_IS_FLOATING_POINT
    template<class Type>
    struct is_floating_point : std::integral_constant<bool,
                                                      std::is_same<float, typename std::remove_cv<Type>::type>::value
                                                      || std::is_same<double, typename std::remove_cv<Type>::type>::value
                                                      || std::is_same<long double, typename std::remove_cv<Type>::type>::value>
    {
    };
#endif //SUNDEW_COMPILER_SUPPORTS_IS_FLOATING_POINT

#if ! SUNDEW_COMPILER_SUPPORTS_IS_ARITHMETIC
    template<class Type>
    struct is_arithmetic : std::integral_constant<bool,
                                                  std::is_integral<Type>::value
                                                  || std::is_floating_point<Type>::value>
    {
    };
#endif //SUNDEW_COMPILER_SUPPORTS_IS_ARITHMETIC

#if ! SUNDEW_COMPILER_SUPPORTS_IS_UNSIGNED
    namespace detail
    {
        template<typename Type, bool = std::is_arithmetic<Type>::value>
        struct is_unsigned : std::integral_constant<bool, Type (0) < Type (-1)>
        {
        };

        template<typename Type>
        struct is_unsigned<Type, false> : std::false_type
        {
        };
    }

    template<typename Type>
    struct is_unsigned : detail::is_unsigned<Type>::type
    {
    };
#endif //SUNDEW_COMPILER_SUPPORTS_IS_UNSIGNED

#endif //SUNDEW_CPP_BACKPORT_H
