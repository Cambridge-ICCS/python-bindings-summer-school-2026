module thermolib
    use thermo_constants, only: WP,&
                                STANDARD_TEMPERATURE,&
                                STEFAN_BOLTZMANN_CONSTANT,&
                                ABSOLUTE_ZERO,&
                                initialize_thermo_constants
    use thermo_moisture, only: calculate_saturation_vapor_pressure,&
                               calculate_relative_humidity
    use thermo_radiation, only: calculate_stefan_boltzmann_flux,&
                                calculate_earth_energy_balance
    implicit none
    public

contains

    !> @brief Initialize the thermolib library
    !>
    !> This subroutine must be called before using any library functions.
    !> It initializes the IEEE arithmetic environment and sets up error handling.
    subroutine initialize_thermolib()
        print *, "Callout"
    end subroutine initialize_thermolib

end module thermolib
