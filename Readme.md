# C++ Web Dictionary Scraper

A command-line web scraper written in **C++** that fetches dictionary definitions
from **Merriam-Webster** using **libcurl** and extracts structured content using
**libxml2 + XPath**.

This project demonstrates low-level systems programming concepts such as
callback-based I/O, HTML parsing, and safe C/C++ interoperability.

---

## Features

- HTTP requests using **libcurl**
- HTML DOM parsing using **libxml2**
- XPath-based definition extraction
- Manual memory management with correct library-specific cleanup
- Works on macOS (Apple Silicon) and Linux

---

## Example

```bash
./webscraper computer
```

**Output**
```
a programmable electronic device that stores, retrieves, and processes data
```

---

## Build Instructions (macOS)

### Install dependencies

```bash
brew install curl libxml2 pkg-config
```

### Compile

```bash
g++ webscraper.cpp -std=c++17 \
  $(pkg-config --cflags --libs libxml-2.0) \
  -lcurl \
  -o webscraper
```

### Run

```bash
./webscraper hello
```

---

## Tech Stack

- **Language:** C++17
- **Networking:** libcurl
- **Parsing:** libxml2 (HTML + XPath)

---

## Design Notes

- Uses callback-based streaming to handle HTTP responses efficiently
- XPath enables robust querying without manual DOM traversal
- Memory ownership follows library-specific allocation rules
- Designed to be easily refactored into RAII-style C++

---

## Disclaimer

This project is for educational purposes. Website structure changes may require
XPath updates.

---

## Author

Built as a learning project to explore systems-level C++ and web data extraction.

---
