# Introduction #

This page summarize the implementation approach on mpi-skel.

# Details #

Following some ideas found at the Linux kernel source code, opaque datatypes and operation callbacks where used to simplify the task to develop a full fledged application.

# Opaque Datatypes #

To provide an object-oriented interface in a non-object-oriented language, opaque datatypes are used.

A given type\_t struct with its operation will also contain type\_data\_t struct with its private information.

In the case of singleton-like types, a private static variable only accessed thorough its interface is used to hold its reference during his lifetime.


# Callbacks #

Using GCC extensions to the C compiler, a struct declared and initialized with callbacks
is used to drive the application behavior from a pipeline design template.

Just implementing these callbacks will be enough for an application to be included on the framework.