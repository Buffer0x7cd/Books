## Exception control flow ##
There are four different types of exception control flows in a system.

* Interrupt:     
    * These are async in nature. 
    * Example: Signal from a I/O Device, Hardware interrupt for the kernal.
    * Always return to next instruction
    * Timer Interrupt: Used for making sechduling decesions by kernel
* Trap:
    * These are sync in nature
    * Example: System calls like read, write etc.
    * Always return to next instruction
    * NMI: Non maskable interrupt
    * SMI: System management interrupt

* Fault:
    * These are also sync in nature
    * Example: Page Fault
    * Might return to current instruction
* Abort:
    * These are also sync in nature
    * They specify a non recoverable condition
    * Never return

### Linux interface for system calls ###
**Question** : How does the system call get invoked in linux in x86-64 System     
**Ans**:  System call gets invoked by invoking a instruction called syscall and writing the syscall number to the **eax** register.

**Question**: How does the arguments to a system calls were passed ?
**Answer**: the six arguments to a syscall are passed through differen register, starting from %rdi, %rsi, %rdx, %r10, %r8 and %r9. on return %rax contain the return value