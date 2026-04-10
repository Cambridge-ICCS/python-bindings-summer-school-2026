program test_thermolib
    use thermolib
    use, intrinsic :: ieee_arithmetic, only: ieee_is_nan
    implicit none

    ! Initialize the library
    call initialize_thermolib()

end program test_thermolib
