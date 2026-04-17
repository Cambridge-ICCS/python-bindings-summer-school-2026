from skbuild import setup

setup(
    name="plunge",
    version="0.1.0",
    description="Jump into the world of Python extensions (legs first) and make a splash!",
    author="ICCS",
    license="MIT",
    packages=["plunge"],
    package_dir={"": "src"},
    python_requires=">=3.11"
)
