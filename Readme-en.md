# Easy_OS Operating System README

## I. Overview of the operating system

Easy_OS is a simple operating system that integrates core functional modules such as basic process management, device management and basic I/O, file system design and command line interface. It aims to provide users with a basic but comprehensive operating system simulation experience and help users deeply understand the operation of the operating system. The logic of interaction between the line mechanism and various functions.

## II. Details of functional modules

### (I) Basic Process Management

- **Rich job scheduling algorithms**: covering first-come, first-served (FCFS), shortest job priority (SJF) and priority scheduling algorithms. After the user enters the number, name, submission time, required running time and priority of the job, the system efficiently allocates the CPU time slice according to the selected algorithm, accurately calculates the turnover time and the righted turnover time, and fully displays the operation execution process and status changes to help users understand the efficiency of different scheduling strategies. And the impact of the balance of resource allocation, and lay a solid foundation for an in-depth understanding of the core principle of process scheduling.

- **The simulation scene is realistic and perceivable**: With the fine time simulation and status tracking mechanism, it vividly reproduces the complete life cycle of the operation in the system, and the stages from submission, readiness, operation to completion are clearly presented, so that users feel like they are in the real operating system environment and deeply understand the process state change and scheduling decision. The dynamic interaction process strengthens the grasp of the complex logical context of process management.

### (II) Equipment Management and Basic I/O

- **Mouse device control is easy**: A complete set of mouse device management functions, from initialization, on and off operations to accurate simulation of mobile event processing. When initializing, the system allocates memory space for the mouse device and initializes each parameter. After turning on, it can receive and efficiently process mobile instructions. When it is turned off, it can properly release resources and reset the state, build intuitive device management practice scenarios for users, and deepen the understanding of device drive and control principles.

- **SPOOLING SYSTEM OPERATES EFFICIENTLY**: DRIVE THE DATA TRANSMISSION PROCESS WITH TASK QUEUE, AND STRICTLY SIMULATES TASK QUEUING, TRANSMISSION AND INTERRUPT PROCESSING LOGIC. After the task joins the team, the data is transmitted in order. If there is a transmission error (10% probability simulation), the interrupt processing process will be triggered immediately, and the task resources will be released after the retransmission is completed. This process deeply reveals the coordination mechanism of I/O device management and task scheduling, and improves users' cognitive level of device concurrency processing and data reliability guarantee strategies.

### (III) File System Design

- **Directory traversal is clear and intuitive**: The `listDirectory` function accurately traverses the directory structure of the file system according to the input path, recursively retrieves subdirectories at all levels, and outputs the full path of files and subdirectories in the directory in an orderly manner, providing users with a panoramic view of file hierarchy distribution and in-depth optimization. File navigation and resource positioning experience.

- **File reading is accurate and error-free**: The `readFile` function uses a robust file flow processing mechanism to accurately locate and read the content of the user-specified file, and parse and output it to the console line by line. At the same time, it has a strong error handling ability to capture abnormally accurate feedback such as non-existence and insufficient permissions of files. , ensure that the file reading operation is safe, reliable and error-zero, and build a solid defense line for file data access operation.

### (IV) Command line interface

- **Commands are simple but not simple**: Support `ls` and `cat` kernel commands. `ls` is used to display the specified directory content. The format is standardized and the information is complete. It covers core metadata such as file name, type, permission, size and modification time (which can be expanded on demand) to help users quickly grasp the overview of the directory file; `cat` accurately reads and outputs the text content of the file to the terminal, supporting Adaptive processing of a variety of text encoding formats is a powerful assistant for text file viewing and content retrieval.

- **Smooth and smooth interaction experience**: Intelligent command analysis and circular interaction architecture work seamlessly, user input commands respond instantly, error instructions accurately prompt and correct suggestions, and automatically return to the waiting input state after execution, forming an efficient and smooth command interaction closed loop, which greatly improves user operation efficiency and experience comfort. Degree.

## III. System Operation Guide

### (I) Environment construction

- **Compiler adaptation is widely**: This system is written in standard C++ and rigorously tested by mainstream C++ compilers (such as GCC, Clang, etc.) to ensure cross-platform compatibility and stability. Users only need to install the adaptive version compiler and operate according to the regular command line or the compilation process of the integrated development environment.

- **Deliance library is lightweight and easy to match**: Rely on the `std::experimental::filesystem` library to realize advanced file system operation. Most modern C++ standard libraries have integrated this function. In case of compatibility problems, the corresponding header will be introduced according to the official document of the compiler. The file and library file link instructions can be easily solved.

### (II) Steps for use

1. **Start selection**: After running the program, enter `y` according to the prompts to enter the main interface of the operating system and start the functional exploration journey; enter `n` to exit the program elegantly, and the operation is simple and clear.

Two. **Main interface navigation**: The main interface presents a clear function menu, and the number keys correspond to the entrance of each functional module. Users enter the corresponding numbers on demand, such as `1` to activate the basic process management module, and the system will immediately guide you to the corresponding functional process. The whole process is intimate and interactive and friendly.

3. **Functional Operation Guidelines**

- **Basic process management**: Enter the key parameters of the job in order according to the screen prompts. After selecting the scheduling algorithm, the system automatically simulates the execution, and the detailed results and statistical information are displayed in real time, which is clear at a glance.

- **Equipment management and basic I/O**: The mouse device management link closely follows the guidance of the system, and the input operation instructions can be operated in real time; the SPOOLING system automatically processes the task queue, and users can focus on observing the task flow and transmission status monitoring to deeply appreciate device management and data transmission. Exquisite.

- **File system design**: In the file operation function, accurately enter the directory or file path according to the prompts, the system responds quickly, and the file system structure and content are immediately presented in front of you, which is convenient and efficient.

- **Command line interface**: In the command line interaction, enter the legal command (`ls` or `cat`) and the corresponding path parameters, and the system will immediately feedback accurate results; enter `exit` to seamlessly return to the main interface, and the interactive experience is smooth and smooth.

## IV. Contribution and Feedback

- **Open source co-creation invitation**: Easy_OS adheres to the spirit of open source and warmly welcomes developers to contribute to code. Whether it is optimizing algorithm efficiency, expanding functional boundaries, repairing potential vulnerabilities or strengthening document completeness, any contribution is a key force to promote system evolution and work together to build an open source ecological model.

- **Feedback communication bridge**: User feedback is the core driving force for system improvement. If you encounter any problems or have suggestions, you can talk freely in the Issue area of the GitHub project and detail the problem reproduction steps and expected performance. The team will make every effort to respond, accurately locate, repair quickly, and continuously optimize the system quality and user experience.