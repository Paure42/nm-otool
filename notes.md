
# Table of Contents

1.  [Behavior](#orgaf04a0b)
    1.  [Basics](#org5baaffc)
    2.  [Symbols](#org5b678c5)
2.  [Exceptions](#org732236a)



<a id="orgaf04a0b"></a>

# Behavior


<a id="org5baaffc"></a>

## Basics

GNU nm lists the symbols from object files objfile.
For each symbol, nm shows:

-   â€¢ The symbol value, in the radix selected by options (see below), or hexadecimal by default.

-   â€¢ The symbol type. At least the following types are used; others are, as well, depending on the object file format. If lowercase, the symbol is local; if uppercase, the symbol is global (external).


<a id="org5b678c5"></a>

## Symbols

-   &ldquo;A&rdquo; = The symbol value is absolute, and will not be changed by further linking

-   &ldquo;B&rdquo; or &ldquo;b&rdquo; = The symbol is in the ununitialized data sections (known as BSS).

-   &ldquo;C&rdquo; = The symbol is common. Common symbols are uninitialized data. When linking, multiple common symbols may appear with the same name. If the symbol is defined anywhere, the common symbols are treated as undefined references.

-   &ldquo;D&rdquo; or &ldquo;d&rdquo; = The symbol is in the initialized section

-   &ldquo;G&rdquo; or &ldquo;g&rdquo; = The symbol is in an initialized data section for small objects. Some object file formats permit more efficient access to small data objects, such as a global int variable as opposed to a large global array.

-   &ldquo;i&rdquo; = For PE format files this indicates that the symbol is in a section specific to the implementation of DLLs. For ELF format files this indicates that the symbol is an indirect function. This is a GNU extension to the standard set of ELF symbol types. It indicates a symbol which if referenced by a relocation does not evaluate to its address, but instead must be invoked at runtime. The runtime execution will then return the value to be used in the relocation.

-   &ldquo;N&rdquo; = The symbol is a debugging symbol.

-   &ldquo;p&rdquo; = The symbols is in a stack unwind section.

-   &ldquo;R&rdquo; or &ldquo;r&rdquo; = The symbol is in a read only section

-   &ldquo;S&rdquo; or &ldquo;s&rdquo; = The symbol is in an uninitialized data section for small objects.

-   &ldquo;T&rdquo; or &ldquo;t&rdquo; = The symbol is in the text (code) section.

-   &ldquo;U&rdquo; = The symbol is undefined.

-   &ldquo;u&rdquo; = The symbol is a unique global symbol. This is a GNU extension to the standard set of ELF symbol bindings. For such a symbol the dynamic linker will make sure that in the entire process there is just one symbol with this name and type in use.

-   &ldquo;V&rdquo; or &ldquo;v&rdquo; = The symbol is a weak object. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the weak symbol becomes zero with no error. On some systems, uppercase indicates that a default value has been specified.

-   &ldquo;W&rdquo; or &ldquo;w&rdquo; = The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. When a weak defined symbol is linked with a normal defined symbol, the normal defined symbol is used with no error. When a weak undefined symbol is linked and the symbol is not defined, the value of the symbol is determined in a system-specific manner without error. On some systems, uppercase indicates that a default value has been specified.

-   &ldquo;-&rdquo; = The symbol is a stabs symbol in an a.out object file. In this case, the next values printed are the stabs other field, the stabs desc field, and the stab type. Stabs symbols are used to hold debugging information.

-   &ldquo;?&rdquo; = The symbol type is unknown, or object file format specific.


<a id="org732236a"></a>

# Exceptions

-   If no object files are listed as arguments, nm assumes the file a.out.

