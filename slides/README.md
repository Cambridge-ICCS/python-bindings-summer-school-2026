# Slides: Local Build Instructions

This folder contains the Quarto source for the slide deck.

## Dependencies

Use the pinned packages in `requirements.txt` as a known, working frozen environment.
You need:

- Python 3.12
- Quarto CLI
- Python packages from `requirements.txt` (includes `numpy` and `jupyter`)

Verify that Quarto is installed:

```bash
quarto --version
```

Quarto installation instructions: https://quarto.org/docs/get-started/

## Build Locally

From this `slides/` directory:

```bash
# Create a local virtual environment in ./venv
python -m venv .venv
```

Activate the virtual environment for your current shell session:

```bash
source .venv/bin/activate
```

Install Python dependencies into the active virtual environment:

```bash
python -m pip install --upgrade pip
python -m pip pip install -r requirements.txt
```

Render the slide deck:

```bash
quarto render index.qmd --output-dir _site/
```

The generated [reveal.js](https://revealjs.com/) presentation will be in `_site/`.
