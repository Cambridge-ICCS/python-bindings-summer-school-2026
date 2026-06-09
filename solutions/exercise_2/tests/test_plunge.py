import pytest
import plunge_pyb
import wurlitzer
import numpy as np


def test_splash_prints(capsys):
    with wurlitzer.sys_pipes():
        plunge_pyb.splash("Alice")
    captured = capsys.readouterr()
    assert "Alice made a splash!🌊" in captured.out


def test_raise_exception():
    plunge_pyb.raise_exception(False)

    with pytest.raises(RuntimeError):
        plunge_pyb.raise_exception(True)


def test_multiple_splash_prints_correct_count(capsys):
    with wurlitzer.sys_pipes():
        plunge_pyb.multiple_splash("Bob", 3)
    captured = capsys.readouterr()
    assert captured.out.count("Bob made a splash!🌊") == 3


def test_multiple_splash_zero_count_prints_nothing(capsys):
    with wurlitzer.sys_pipes():
        plunge_pyb.multiple_splash("Bob", 0)
    captured = capsys.readouterr()
    assert captured.out == ""


def test_multiple_splash_invalid_input():
    with pytest.raises(ValueError):
        plunge_pyb.multiple_splash("Bob", -1)


def test_print_numpy_array_prints_size_and_values(capsys):
    with wurlitzer.sys_pipes():
        plunge_pyb.print_numpy_array(np.array([1.0, 2.5, 3.0]))

    captured = capsys.readouterr()
    assert "Size: 3" in captured.out
    assert "1" in captured.out
    assert "2.5" in captured.out
    assert "3" in captured.out


def test_apply_on_range_returns_transformed_values():
    result = plunge_pyb.apply_on_range(lambda value: value * value, 0, 4)
    np.testing.assert_array_equal(result, np.array([0.0, 1.0, 4.0, 9.0]))


def test_apply_on_range_handles_non_zero_start():
    result = plunge_pyb.apply_on_range(lambda value: value + 10, 2, 5)
    np.testing.assert_array_equal(result, np.array([12.0, 13.0, 14.0]))


def test_apply_on_range_returns_empty_array_for_empty_range():
    result = plunge_pyb.apply_on_range(lambda value: value, 3, 3)
    assert result.shape == (0,)


@pytest.mark.parametrize("interpolate_function", [plunge_pyb.interpolate, plunge_pyb.interpolate_np])
class TestInterpolate:
    def test_interpolate_returns_function_values_on_grid(self, interpolate_function):
        grid = np.array([0.0, 0.5, 1.5])
        result = interpolate_function(lambda value: value * 2.0, grid)
        # Result is a sequence but may be numpy array or list
        # Cast to list
        result = list(result)
        assert result == [0.0, 1.0, 3.0]

    def test_interpolate_returns_empty_list_for_empty_grid(self, interpolate_function):
        result = interpolate_function(lambda value: value + 1.0, np.array([]))
        # Result is a sequence but may be numpy array or list
        # Cast to list
        result = list(result)
        assert result == []
