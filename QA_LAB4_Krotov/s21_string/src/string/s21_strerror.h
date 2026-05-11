#ifndef S21_STRERROR_H
#define S21_STRERROR_H

#include "s21_string.h"

#if __linux__
static const char *S21_ERRORS[] = {
    "Success",                                 // 0
    "Operation not permitted",                 // EPERM 1
    "No such file or directory",               // ENOENT 2
    "No such process",                         // ESRCH 3
    "Interrupted system call",                 // EINTR 4
    "Input/output error",                      // EIO 5
    "No such device or address",               // ENXIO 6
    "Argument list too long",                  // E2BIG 7
    "Exec format error",                       // ENOEXEC 8
    "Bad file descriptor",                     // EBADF 9
    "No child processes",                      // ECHILD 10
    "Resource temporarily unavailable",        // EAGAIN 11 EWOULDBLOCK 41
    "Cannot allocate memory",                  // ENOMEM 12
    "Permission denied",                       // EACCES 13
    "Bad address",                             // EFAULT 14
    "Block device required",                   // ENOTBLK 15
    "Device or resource busy",                 // EBUSY 16
    "File exists",                             // EEXIST 17
    "Invalid cross-device link",               // EXDEV 18
    "No such device",                          // ENODEV 19
    "Not a directory",                         // ENOTDIR 20
    "Is a directory",                          // EISDIR 21
    "Invalid argument",                        // EINVAL 22
    "Too many open files in system",           // ENFILE 23
    "Too many open files",                     // EMFILE 24
    "Inappropriate ioctl for device",          // ENOTTY 25
    "Text file busy",                          // ETXTBSY 26
    "File too large",                          // EFBIG 27
    "No space left on device",                 // ENOSPC 28
    "Illegal seek",                            // ESPIPE 29
    "Read-only file system",                   // EROFS 30
    "Too many links",                          // EMLINK 31
    "Broken pipe",                             // EPIPE 32
    "Numerical argument out of domain",        // EDOM 33
    "Numerical result out of range",           // ERANGE 34
    "Resource deadlock avoided",               // EDEADLK 35
    "File name too long",                      // ENAMETOOLONG 36
    "No locks available",                      // ENOLCK 37
    "Function not implemented",                // ENOSYS 38
    "Directory not empty",                     // ENOTEMPTY 39
    "Too many levels of symbolic links",       // ELOOP 40
    "Unknown error 41",                        // EWOULDBLOCK 41 EAGAIN 11
    "No message of desired type",              // ENOMSG 42
    "Identifier removed",                      // EIDRM 43
    "Channel number out of range",             // ECHRNG 44
    "Level 2 not synchronized",                // EL2NSYNC 45
    "Level 3 halted",                          // EL3HLT 46
    "Level 3 reset",                           // EL3RST 47
    "Link number out of range",                // ELNRNG 48
    "Protocol driver not attached",            // EUNATCH 49
    "No CSI structure available",              // ENOCSI 50
    "Level 2 halted",                          // EL2HLT 51
    "Invalid exchange",                        // EBADE 52
    "Invalid request descriptor",              // EBADR 53
    "Exchange full",                           // EXFULL 54
    "No anode",                                // ENOANO 55
    "Invalid request code",                    // EBADRQC 56
    "Invalid slot",                            // EBADSLT 57
    "Unknown error 58",                        // EDEADLOCK 58 EDEADLK 35
    "Bad font file format",                    // EBFONT 59
    "Device not a stream",                     // ENOSTR 60
    "No data available",                       // ENODATA 61
    "Timer expired",                           // ETIME 62
    "Out of streams resources",                // ENOSR 63
    "Machine is not on the network",           // ENONET 64
    "Package not installed",                   // ENOPKG 65
    "Object is remote",                        // EREMOTE 66
    "Link has been severed",                   // ENOLINK 67
    "Advertise error",                         // EADV 68
    "Srmount error",                           // ESRMNT 69
    "Communication error on send",             // ECOMM 70
    "Protocol error",                          // EPROTO 71
    "Multihop attempted",                      // EMULTIHOP 72
    "RFS specific error",                      // EDOTDOT 73
    "Bad message",                             // EBADMSG 74
    "Value too large for defined data type",   // EOVERFLOW 75
    "Name not unique on network",              // ENOTUNIQ 76
    "File descriptor in bad state",            // EBADFD 77
    "Remote address changed",                  // EREMCHG 78
    "Can not access a needed shared library",  // ELIBACC 79
    "Accessing a corrupted shared library",    // ELIBBAD 80
    ".lib section in a.out corrupted",         // ELIBSCN 81
    "Attempting to link in too many shared libraries",    // ELIBMAX 82
    "Cannot exec a shared library directly",              // ELIBEXEC 83
    "Invalid or incomplete multibyte or wide character",  // EILSEQ 84
    "Interrupted system call should be restarted",        // ERESTART 85
    "Streams pipe error",                                 // ESTRPIPE 86
    "Too many users",                                     // EUSERS 87
    "Socket operation on non-socket",                     // ENOTSOCK 88
    "Destination address required",                       // EDESTADDRREQ 89
    "Message too long",                                   // EMSGSIZE 90
    "Protocol wrong type for socket",                     // EPROTOTYPE 91
    "Protocol not available",                             // ENOPROTOOPT 92
    "Protocol not supported",                             // EPROTONOSUPPORT 93
    "Socket type not supported",                          // ESOCKTNOSUPPORT 94
    "Operation not supported",                            // EOPNOTSUPP 95
    "Protocol family not supported",                      // EPFNOSUPPORT 96
    "Address family not supported by protocol",           // EAFNOSUPPORT 97
    "Address already in use",                             // EADDRINUSE 98
    "Cannot assign requested address",                    // EADDRNOTAVAIL 99
    "Network is down",                                    // ENETDOWN 100
    "Network is unreachable",                             // ENETUNREACH 101
    "Network dropped connection on reset",                // ENETRESET 102
    "Software caused connection abort",                   // ECONNABORTED 103
    "Connection reset by peer",                           // ECONNRESET 104
    "No buffer space available",                          // ENOBUFS 105
    "Transport endpoint is already connected",            // EISCONN 106
    "Transport endpoint is not connected",                // ENOTCONN 107
    "Cannot send after transport endpoint shutdown",      // ESHUTDOWN 108
    "Too many references: cannot splice",                 // ETOOMANYREFS 109
    "Connection timed out",                               // ETIMEDOUT 110
    "Connection refused",                                 // ECONNREFUSED 111
    "Host is down",                                       // EHOSTDOWN 112
    "No route to host",                                   // EHOSTUNREACH 113
    "Operation already in progress",                      // EALREADY 114
    "Operation now in progress",                          // EINPROGRESS 115
    "Stale file handle",                                  // ESTALE 116
    "Structure needs cleaning",                           // EUCLEAN 117
    "Not a XENIX named type file",                        // ENOTNAM 118
    "No XENIX semaphores available",                      // ENAVAIL 119
    "Is a named type file",                               // EISNAM 120
    "Remote I/O error",                                   // EREMOTEIO 121
    "Disk quota exceeded",                                // EDQUOT 122
    "No medium found",                                    // ENOMEDIUM 123
    "Wrong medium type",                                  // EMEDIUMTYPE 124
    "Operation canceled",                                 // ECANCELED 125
    "Required key not available",                         // ENOKEY 126
    "Key has expired",                                    // EKEYEXPIRED 127
    "Key has been revoked",                               // EKEYREVOKED 128
    "Key was rejected by service",                        // EKEYREJECTED 129
    "Owner died",                                         // EOWNERDEAD 130
    "State not recoverable",                              // ENOTRECOVERABLE 131
    "Operation not possible due to RF-kill",              // ERFKILL 132
    "Memory page has hardware error",                     // EHWPOISON 133
    "Unknown error 134"  // ENOTSUP 134 EOPNOTSUPP 95
};
#elif defined(__APPLE__)

static const char *S21_ERRORS[] = {
    "Undefined error: 0",                 // 0 Error
    "Operation not permitted",            // 1 EPERM
    "No such file or directory",          // 2 ENOENT
    "No such process",                    // 3 ESRCH
    "Interrupted system call",            // 4 EINTR
    "Input/output error",                 // 5 EIO
    "Device not configured",              // 6 ENXIO
    "Argument list too long",             // 7 E2BIG
    "Exec format error",                  // 8 ENOEXEC
    "Bad file descriptor",                // 9 EBADF
    "No child processes",                 // 10 ECHILD
    "Resource deadlock avoided",          // 11 EDEADLK EAGAIN
    "Cannot allocate memory",             // 12 ENOMEM
    "Permission denied",                  // 13 EACCES
    "Bad address",                        // 14 EFAULT
    "Block device required",              // 15 ENOTBLK
    "Resource busy",                      // 16 EBUSY
    "File exists",                        // 17 EEXIST
    "Cross-device link",                  // 18 EXDEV
    "Operation not supported by device",  // 19 ENODEV
    "Not a directory",                    // 20 ENOTDIR
    "Is a directory",                     // 21 EISDIR
    "Invalid argument",                   // 22 EINVAL
    "Too many open files in system",      // 23 ENFILE
    "Too many open files",                // 24 EMFILE
    "Inappropriate ioctl for device",     // 25 ENOTTY
    "Text file busy",                     // 26 ETXTBSY
    "File too large",                     // 27 EFBIG
    "No space left on device",            // 28 ENOSPC
    "Illegal seek",                       // 29 ESPIPE
    "Read-only file system",              // 30 EROFS
    "Too many links",                     // 31 EMLINK
    "Broken pipe",                        // 32 EPIPE
    "Numerical argument out of domain",   // 33 EDOM
    "Result too large",                   // 34 ERANGE
    "Resource temporarily unavailable",   // 35 EAGAIN EWOULDBLOCK /* Operation
                                          // would block */
    "Operation now in progress",          // 36 EINPROGRESS
    "Operation already in progress",      // 37 EALREADY
    "Socket operation on non-socket",     // 38 ENOTSOCK
    "Destination address required",       // 39 EDESTADDRREQ
    "Message too long",                   // 40 EMSGSIZE
    "Protocol wrong type for socket",     // 41 EPROTOTYPE
    "Protocol not available",             // 42 ENOPROTOOPT
    "Protocol not supported",             // 43 EPROTONOSUPPORT
    "Socket type not supported",          // 44 ESOCKTNOSUPPORT
    "Operation not supported",            // 45 ENOTSUP | could be EOPNOTSUPP
    "Protocol family not supported",      // 46 EPFNOSUPPORT
    "Address family not supported by protocol family",  // 47 EAFNOSUPPORT
    "Address already in use",                           // 48 EADDRINUSE
    "Can't assign requested address",                   // 49 EADDRNOTAVAIL
    "Network is down",                                  // 50 ENETDOWN
    "Network is unreachable",                           // 51 ENETUNREACH
    "Network dropped connection on reset",              // 52 ENETRESET
    "Software caused connection abort",                 // 53 ECONNABORTED
    "Connection reset by peer",                         // 54 ECONNRESET
    "No buffer space available",                        // 55 ENOBUFS
    "Socket is already connected",                      // 56 EISCONN
    "Socket is not connected",                          // 57 ENOTCONN
    "Can't send after socket shutdown",                 // 58 ESHUTDOWN
    "Too many references: can't splice",                // 59 ETOOMANYREFS
    "Operation timed out",                              // 60 ETIMEDOUT
    "Connection refused",                               // 61 ECONNREFUSED
    "Too many levels of symbolic links",                // 62 ELOOP
    "File name too long",                               // 63 ENAMETOOLONG
    "Host is down",                                     // 64 EHOSTDOWN
    "No route to host",                                 // 65 EHOSTUNREACH
    "Directory not empty",                              // 66 ENOTEMPTY
    "Too many processes",                               // 67 EPROCLIM
    "Too many users",                                   // 68 EUSERS
    "Disc quota exceeded",                              // 69 EDQUOT
    "Stale NFS file handle",                            // 70 ESTALE
    "Too many levels of remote in path",                // 71 EREMOTE
    "RPC struct is bad",                                // 72 EBADRPC
    "RPC version wrong",                                // 73 ERPCMISMATCH
    "RPC prog. not avail",                              // 74 EPROGUNAVAIL
    "Program version wrong",                            // 75 EPROGMISMATCH
    "Bad procedure for program",                        // 76 EPROCUNAVAIL
    "No locks available",                               // 77 ENOLCK
    "Function not implemented",                         // 78 ENOSYS
    "Inappropriate file type or format",                // 79 EFTYPE
    "Authentication error",                             // 80 EAUTH
    "Need authenticator",                               // 81 ENEEDAUTH
    "Device power is off",                              // 82 EPWROFF
    "Device error",                                     // 83 EDEVERR
    "Value too large to be stored in data type",        // 84 EOVERFLOW
    "Bad executable (or shared library)",               // 85 EBADEXEC
    "Bad CPU type in executable",                       // 86 EBADARCH
    "Shared library version mismatch",                  // 87 ESHLIBVERS
    "Malformed Mach-o file",                            // 88 EBADMACHO
    "Operation canceled",                               // 89 ECANCELED
    "Identifier removed",                               // 90 EIDRM
    "No message of desired type",                       // 91 ENOMSG
    "Illegal byte sequence",                            // 92 EILSEQ
    "Attribute not found",                              // 93 ENOATTR
    "Bad message",                                      // 94 EBADMSG
    "EMULTIHOP (Reserved)",                             // 95 EMULTIHOP
    "No message available on STREAM",                   // 96 ENODATA
    "ENOLINK (Reserved)",                               // 97 ENOLINK
    "No STREAM resources",                              // 98 ENOSR
    "Not a STREAM",                                     // 99 ENOSTR
    "Protocol error",                                   // 100 EPROTO
    "STREAM ioctl timeout",                             // 101 ETIME
    "Operation not supported on socket",                // 102 EOPNOTSUPP
    "Policy not found",                                 // 103 ENOPOLICY
    "State not recoverable",                            // 104 ENOTRECOVERABLE
    "Previous owner died",                              // 105 EOWNERDEAD
    "Interface output queue is full"  // 106 EQFULL probably also ELAST
};

#endif

#endif