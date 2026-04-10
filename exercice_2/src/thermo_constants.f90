module thermo_constants
    use, intrinsic :: ieee_arithmetic, only: ieee_value, ieee_quiet_nan
    implicit none
    private

    !> @public
    !> @brief Working precision - double precision floating point
    public :: WP

    !> @public
    !> @brief Error value - IEEE quiet NaN for invalid inputs
    public :: ERROR_NAN

    !> @public
    !> @brief Stefan-Boltzmann constant (W/(m²·K⁴))
    public :: STEFAN_BOLTZMANN_CONSTANT

    !> @public
    !> @brief Standard atmospheric temperature (K)
    public :: STANDARD_TEMPERATURE

    !> @public
    !> @brief Absolute zero temperature (K)
    public :: ABSOLUTE_ZERO

    !> @public
    !> @brief Validate temperature input
    public :: check_temperature

    !> @public
    !> @brief Validate vapor pressure input
    public :: check_vapor_pressure

    !> @public
    !> @brief Validate albedo input
    public :: check_albedo

    !> @public
    !> @brief Initialize the thermo_constants module
    public :: initialize_thermo_constants

    ! Define working precision - double precision
    integer, parameter :: WP = kind(1.0d0)

    ! Error handling - return IEEE quiet NaN for invalid inputs
    real(WP) :: ERROR_NAN

    ! Fundamental physical constants
    real(WP), parameter :: STEFAN_BOLTZMANN_CONSTANT = 5.670374419e-8_WP
    real(WP), parameter :: STANDARD_TEMPERATURE = 288.15_WP
    real(WP), parameter :: ABSOLUTE_ZERO = 0.0_WP

    ! Error messages for debugging (not exposed to users)
    character(len=*), parameter, private :: ERROR_TEMPERATURE = "Temperature must be above absolute zero"
    character(len=*), parameter, private :: ERROR_VAPOR_PRESSURE = "Vapor pressure cannot be negative"
    character(len=*), parameter, private :: ERROR_ALBEDO = "Albedo must be between 0 and 1"

contains

    !> @brief Validate temperature input
    !>
    !> @param temperature Temperature in Kelvin (K)
    !> @return .true. if temperature is valid (> 0 K), .false. otherwise
    pure function check_temperature(temperature) result(is_valid)
        real(WP), intent(in) :: temperature
        logical :: is_valid
        is_valid = temperature > ABSOLUTE_ZERO
    end function check_temperature

    !> @brief Validate vapor pressure input
    !>
    !> @param vapor_pressure Vapor pressure in Pascals (Pa)
    !> @return .true. if vapor pressure is valid (≥ 0), .false. otherwise
    pure function check_vapor_pressure(vapor_pressure) result(is_valid)
        real(WP), intent(in) :: vapor_pressure
        logical :: is_valid
        is_valid = vapor_pressure >= 0.0_WP
    end function check_vapor_pressure

    !> @brief Validate albedo input
    !>
    !> @param albedo Albedo value (0-1)
    !> @return .true. if albedo is valid (0.0 ≤ albedo ≤ 1.0), .false. otherwise
    pure function check_albedo(albedo) result(is_valid)
        real(WP), intent(in) :: albedo
        logical :: is_valid
        is_valid = (albedo >= 0.0_WP) .and. (albedo <= 1.0_WP)
    end function check_albedo

    !> @brief Initialize the thermo_constants module
    !>
    !> This subroutine must be called before using the library to initialize
    !> the ERROR_NAN value.
    subroutine initialize_thermo_constants()
        ERROR_NAN = ieee_value(0.0_WP, IEEE_QUIET_NAN)
    end subroutine initialize_thermo_constants

end module thermo_constants
