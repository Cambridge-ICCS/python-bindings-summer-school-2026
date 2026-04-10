module thermo_radiation
    use thermo_constants, only: WP, ERROR_NAN, STEFAN_BOLTZMANN_CONSTANT, check_temperature, check_albedo
    implicit none
    private

    public :: calculate_stefan_boltzmann_flux
    public :: calculate_earth_energy_balance

contains

    !> @brief Calculate outgoing longwave radiation using Stefan-Boltzmann law
    !>
    !> This function implements the Stefan-Boltzmann law: F = σ*T⁴, where σ is the
    !> Stefan-Boltzmann constant and T is the absolute temperature.
    !>
    !> @param temperature Temperature in Kelvin (K)
    !> @return Radiative flux in watts per square meter (W/m²), or NaN for invalid input
    !>
    !> @details
    !> - Implements the fundamental physical law: F = σ*T⁴
    !> - Uses SI units: temperature in Kelvin, flux in W/m²
    !> - Returns IEEE quiet NaN for invalid inputs (temperature ≤ 0 K)
    !> - Stefan-Boltzmann constant: 5.670374419×10⁻⁸ W/(m²·K⁴)
    !>
    !> @see https://en.wikipedia.org/wiki/Stefan–Boltzmann_law
    pure function calculate_stefan_boltzmann_flux(temperature) result(flux)
        real(WP), intent(in) :: temperature
        real(WP) :: flux

        ! Validate input - temperature must be above absolute zero
        if (.not. check_temperature(temperature)) then
            flux = ERROR_NAN
            return
        end if

        ! Apply Stefan-Boltzmann law: F = σ*T⁴
        flux = STEFAN_BOLTZMANN_CONSTANT * temperature**4
    end function calculate_stefan_boltzmann_flux

    !> @brief Calculate Earth's effective temperature from energy balance
    !>
    !> This function calculates the Earth's effective radiating temperature based on
    !> the balance between incoming solar radiation and outgoing longwave radiation.
    !>
    !> @param albedo Earth's albedo (0-1), fraction of sunlight reflected (optional, default: 0.3)
    !> @param solar_constant Solar constant in W/m² (optional, default: 1361.0 W/m²)
    !> @return Effective temperature in Kelvin (K), or NaN for invalid input
    !>
    !> @details
    !> - Uses the formula: T = [(S(1-A))/(4σ)]^(1/4)
    !> - S: solar constant (W/m²)
    !> - A: albedo (0-1, fraction of sunlight reflected)
    !> - σ: Stefan-Boltzmann constant
    !> - Returns IEEE quiet NaN for invalid albedo values (outside [0,1] range)
    !> - Default values: albedo = 0.3 (Earth's average), solar_constant = 1361.0 W/m²
    !>
    !> @see https://en.wikipedia.org/wiki/Effective_temperature
    pure function calculate_earth_energy_balance(albedo, solar_constant) result(effective_temp)
        real(WP), intent(in), optional :: albedo
        real(WP), intent(in), optional :: solar_constant
        real(WP) :: effective_temp
        real(WP) :: local_albedo, local_solar_constant

        ! Set default values for optional parameters
        local_albedo = 0.3_WP          ! Earth's average albedo
        local_solar_constant = 1361.0_WP ! Current solar constant

        ! Use provided values if present
        if (present(albedo)) local_albedo = albedo
        if (present(solar_constant)) local_solar_constant = solar_constant

        ! Validate albedo - must be between 0 and 1
        if (.not. check_albedo(local_albedo)) then
            effective_temp = ERROR_NAN
            return
        end if

        ! Calculate effective temperature using energy balance equation
        ! T = [(S(1-A))/(4σ)]^(1/4)
        effective_temp = (local_solar_constant * (1.0_WP - local_albedo) / &
                         (4.0_WP * STEFAN_BOLTZMANN_CONSTANT)) ** 0.25_WP
    end function calculate_earth_energy_balance

end module thermo_radiation
