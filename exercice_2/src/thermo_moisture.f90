module thermo_moisture
    use thermo_constants, only: WP, ERROR_NAN, check_temperature, check_vapor_pressure
    use, intrinsic :: ieee_arithmetic, only: ieee_is_nan
    implicit none
    private

    public :: calculate_saturation_vapor_pressure
    public :: calculate_relative_humidity

contains

    !> @brief Calculate saturation vapor pressure over liquid and ice
    !>
    !> This function calculates the saturation vapor pressure using empirical formulas
    !> from Buck (1981). It automatically selects the appropriate formula based on
    !> whether the temperature is above or below freezing.
    !>
    !> @param temperature Temperature in Kelvin (K)
    !> @return Saturation vapor pressure in Pascals (Pa), or NaN for invalid input
    !>
    !> @details
    !> - For temperatures above freezing (T > 0°C): Uses liquid water formula
    !> - For temperatures at or below freezing (T ≤ 0°C): Uses ice formula
    !> - Returns IEEE quiet NaN for invalid inputs (temperature ≤ 0 K)
    !>
    !> @see Buck, A. L., "New equations for computing vapor pressure and enhancement factor,"
    !>      J. Appl. Meteorol., 20, 1527-1532, 1981
    pure function calculate_saturation_vapor_pressure(temperature) result(svp)
        real(WP), intent(in) :: temperature
        real(WP) :: svp
        real(WP) :: temp_c  ! Temperature in Celsius

        ! Validate input - temperature must be above absolute zero
        if (.not. check_temperature(temperature)) then
            svp = ERROR_NAN
            return
        end if

        ! Convert temperature from Kelvin to Celsius for empirical formulas
        temp_c = temperature - 273.15_WP

        ! Select appropriate formula based on temperature
        if (temp_c < 0.0_WP) then
            svp = 611.21_WP * exp(17.502_WP * temp_c / (temp_c + 240.97_WP))
        else
            svp = 611.2_WP * exp(17.67_WP * temp_c / (temp_c + 243.5_WP))
        end if
    end function calculate_saturation_vapor_pressure

    !> @brief Calculate relative humidity
    !>
    !> This function calculates relative humidity as the ratio of actual vapor pressure
    !> to saturation vapor pressure, clipped to the physically meaningful range [0, 1].
    !>
    !> @param vapor_pressure Actual vapor pressure in Pascals (Pa)
    !> @param temperature Temperature in Kelvin (K)
    !> @return Relative humidity as a fraction (0.0 to 1.0), or NaN for invalid input
    !>
    !> @details
    !> - Calculates RH = vapor_pressure / saturation_vapor_pressure
    !> - Clips result to [0.0, 1.0] range to ensure physical validity
    !> - Returns IEEE quiet NaN for invalid inputs (negative vapor pressure or invalid temperature)
    !> - Handles supersaturation by clipping to 1.0 (100% RH)
    pure function calculate_relative_humidity(vapor_pressure, temperature) result(rh)
        real(WP), intent(in) :: vapor_pressure
        real(WP), intent(in) :: temperature
        real(WP) :: rh
        real(WP) :: sat_vp  ! Saturation vapor pressure

        ! Validate inputs
        if (.not. check_vapor_pressure(vapor_pressure) .or. .not. check_temperature(temperature)) then
            rh = ERROR_NAN
            return
        end if

        ! Calculate saturation vapor pressure for given temperature
        sat_vp = calculate_saturation_vapor_pressure(temperature)

        ! Check if saturation vapor pressure calculation failed
        if (ieee_is_nan(sat_vp)) then
            rh = ERROR_NAN
            return
        end if

        ! Calculate relative humidity and clip to valid range [0.0, 1.0]
        ! This handles both subsaturation and supersaturation cases
        rh = min(max(vapor_pressure / sat_vp, 0.0_WP), 1.0_WP)
    end function calculate_relative_humidity

end module thermo_moisture
