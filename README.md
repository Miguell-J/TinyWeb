# TinyWeb Server

![TinyWeb Banner](https://img.shields.io/badge/TinyWeb-HTTP_Server-green)

## Overview

TinyWeb is a simple HTTP web server written in C that handles basic HTTP requests on port 80 and serves static files from a configurable directory (`./webroot`).  
It’s perfect for learning and experimenting with sockets, file handling, and network programming in C.

---

## Features

- Handles HTTP GET requests on port 80  
- Serves static files from the `webroot` directory  
- Supports sequential multiple connections  
- Returns 404 responses for missing files  
- Minimalistic, straightforward, and easy-to-understand implementation  

---

## Requirements

- Compatible C compiler (gcc, clang)  
- Unix-like system (Linux, macOS) recommended  
- Network configured to allow connections on port 80  

---

## Installation

Clone the repository and compile:

```bash
git clone https://github.com/yourusername/tinyweb.git
cd tinyweb
gcc -o tinyweb tinyweb.c
````

---

## Usage

Run the server as root (port 80 requires elevated privileges):

```bash
sudo ./tinyweb
```

The server will start listening for HTTP connections on port 80. Place your HTML files and other resources inside the `webroot` folder.

---

## Testing

Open your browser and visit:

```
http://localhost
```

You should see the `index.html` file served from the `webroot` directory. If it does not exist, a 404 response will be returned.

---

## Customization

* Change the port and root directory by editing the macros at the top of `main.c`.
* Add support for multiple MIME types for different file extensions.
* Implement threading for concurrent connections.

---

## Contributing

Contributions are welcome!
Fork the repo, add your feature or fix, and submit a Pull Request.

---

## Contact

Miguel Araújo Julio
[LinkedIn](https://linkedin.com/in/miguell-julio) | [GitHub](https://github.com/miguell-j) | [miguel@example.com](mailto:julioaraujo.guel@gmail.com)

---

**Thank you for checking out TinyWeb!**
Feel free to reach out with questions, suggestions, or collaboration ideas.
