import pytest
import plunge


def test_splash_prints(capsys):
    plunge.splash("Alice")
    captured = capsys.readouterr()
    assert "Alice made a splash!🌊" in captured.out


def test_raise_exception():
    plunge.raise_exception(False)

    with pytest.raises(RuntimeError):
        plunge.raise_exception(True)


def test_multiple_splash_prints_correct_count(capsys):
    plunge.multiple_splash("Bob", 3)
    captured = capsys.readouterr()
    assert captured.out.count("Bob made a splash!🌊") == 3


def test_multiple_splash_zero_count_prints_nothing(capsys):
    plunge.multiple_splash("Bob", 0)
    captured = capsys.readouterr()
    assert captured.out == ""


def test_multiple_splash_invalid_input():
    with pytest.raises(ValueError):
        plunge.multiple_splash("Bob", -1)
