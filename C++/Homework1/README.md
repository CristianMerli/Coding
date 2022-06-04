<h1><b>Homework-1 structure</h1></b>

---

<h2><b>Files and folders for the course TPA: Homework-1.</h2></b>

---

- `data:` folder containing I/O files.
  - `input:` folder containing input matrix and convolution kernel.
  - `output:` folder containing test output matrices.
- `doc:` folder containing project documentation.
  - `abstract:` folder containing project abstract (pdf). [`UNUSED`]
  - `code:` folder containing code documentation (doxygen-html).
  - `files:` folder containing project requests and initial files/data.
- `src:` folder containing source code.
  - `lib:` folder containing code libraries & packages.
  - `main:` folder containing homework main code files.
- `homework.exe:` homework executable generated using makefile.
- `makefile:` use command **make** to compile, ***make run*** to execute or ***make all_run*** to compile and execute. It is also possible to use ***make doc_open*** command, to open code doxygen-html documentation (quick-documentation, not detailed).

---

<h2><b>Notes:</h2></b>

---

- The matrix convolution is applied on input matrix after ReLU operation (which modifies the matrix)!
- All the other operations are directly applied on input matrix.

---
