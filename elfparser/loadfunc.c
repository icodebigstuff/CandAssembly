// Template to complete the loadfunc program which locates a function
// in the text section of an ELF file. Sections that start with a
// CAPITAL in their comments require additions and modifications to
// complete the program (unless marked as PROVIDED).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

int DEBUG = 0;                  // PROVIDED: controls whether to print debug messages

int main(int argc, char **argv){
  if( argc > 1 && strcmp(argv[1], "-d")==0 ){// PROVIDED: command line handling of debug options
    DEBUG = 1;                               // check 1st arg for -d debug
    argv++;                                  // shift forward if found
    argc--;
  }
  if(argc < 3){                              // PROVIDED: command line checks for proper # args
    printf("usage: %s [-d] <file> <funcname> \n",argv[0]);
    return 0;
  }
  char *objfile_name = argv[1];
  char *func_name = argv[2];

  // PROVIDED: open file to get file descriptor
  int fd = open(objfile_name, O_RDWR);       // open file to get file descriptor

  // DETERMINE size of file and create read/write memory map of the file
  // YOUR CODE HERE
  struct stat stat_calc;
  fstat(fd, &stat_calc);
  int size = stat_calc.st_size; // size is size of the file

  // CREATE A POINTER to the intial bytes of the file which are an ELF64_Ehdr struct
  Elf64_Ehdr *ehdr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);

  // CHECK e_ident field's bytes 0 to for for the sequence {0x7f,'E','L','F'}.
  // Exit the program with code 1 if the bytes do not match

  int ident_matches =
  ehdr->e_ident[0] ==0x7f &&
  ehdr->e_ident[1] == 'E' &&
  ehdr->e_ident[2] == 'L' &&
  ehdr->e_ident[3] == 'F';

  if(!ident_matches){
  printf("ERROR: Magic bytes wrong, this is not an ELF file\n");
    exit(1);
  }
  // PROVIDED: check for a 64-bit file
  if(ehdr->e_ident[EI_CLASS] != ELFCLASS64){
    printf("ERROR: Not a 64-bit file ELF file\n");
    // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;
  }

  // PROVIDED: check for x86-64 architecture
  if(ehdr->e_machine != EM_X86_64){
    printf("ERROR: Not an x86-64 file\n");
    // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;
  }
  // could check hear for ehdr->e_ident[EI_OSABI] for ELFOSABI_LINUX


  // DETERMINE THE OFFSET of the Section Header Array (e_shoff), the
  // number of sections (e_shnum), and the index of the Section Header
  // String table (e_shstrndx). These fields are from the ELF File
  // Header.


    Elf64_Off offset = ehdr->e_shoff;
    uint16_t sections = ehdr->e_shnum;
    uint16_t index = ehdr->e_shstrndx;



  // SET UP a pointer to the array of section headers. Use the section
  // header string table index to find its byte position in the file
  // and set up a pointer to it.
  Elf64_Shdr *shdr = (Elf64_Shdr *)((char *) ehdr+offset);
  char *secnames = (char *) ((char *)ehdr + shdr[index].sh_offset);

  // SEARCH the Section Header Array for sections with names .symtab
  // (symbol table) .strtab (string table), and .data (initialized
  // data sections).  Note their positions in the file (sh_offset
  // field).  Also note the size in bytes (sh_size) and and the size
  // of each entry (sh_entsize) for .symtab so its number of entries
  // can be computed. Finally, note the .data section's index (i value
  // in loop) and its load address (sh_addr)

  //16 or 64 uints for variables .

  Elf64_Off str_offset =-1; // string table offset
  Elf64_Off symb_offset =-1; //symbol table offset
  Elf64_Off text_offset =-1;  //text section offset
  uint64_t byt_size =-1; //size in bytes of symbtab
  uint64_t entry_size=-1; //size of entry of symbtab
  uint16_t text_index =-1;  //index of text section
  Elf64_Addr load_address = -1; //load address of text section
  uint64_t entries =-1; //number of entries in symbtab
  int sec_index = -1; //index of section
  for(int i=0; i<sections; i++){

    char *name = secnames+ shdr[i].sh_name; //name of section at position i

    if (strcmp(name, ".symtab") == 0){
        symb_offset  = shdr[i].sh_offset;
        byt_size = shdr[i].sh_size;
        entry_size = shdr[i].sh_entsize;
        entries = byt_size/entry_size;
        sec_index = i;
    }

    if (strcmp(name, ".strtab") == 0){
        str_offset = shdr[i].sh_offset;
    }

    if(strcmp(name, ".text") == 0){
        text_offset = shdr[i].sh_offset;
        text_index =i;
        load_address = shdr[i].sh_addr;
    }

  }

  // ERROR check to ensure everything was found based on things that
  // could not be found.

  if(symb_offset == -1){
    printf("ERROR: Couldn't find symbol table\n");
    // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;
  }


  if(str_offset == -1){
    printf("ERROR: Couldn't find string table\n");
    // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;
  }

  if(text_offset == -1){
    printf("ERROR: Couldn't find text section\n");
    // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;
  }

  // PRINT info on the .text section where function bytes are stored
  char *text_sec = (char *) ehdr + text_offset; //pointer to head of text section
  printf(".text section\n");
  printf("- %hd section index\n",text_index);
  printf("- %lu bytes offset from start of file\n",text_offset);
  printf("- 0x%lx preferred virtual address for .text\n",load_address);


  // PRINT byte information about where the symbol table was found and
  // its sizes. The number of entries in the symbol table can be
  // determined by dividing its total size in bytes by the size of
  // each entry.

  printf(".symtab section\n");
  printf("- %hd section index\n",sec_index);
  printf("- %lu bytes offset from start of file\n", symb_offset);
  printf("- %lu bytes total size\n",byt_size);
  printf("- %lu bytes per entry\n", entry_size);
  printf("- %lu entries\n",entries);


  // SET UP pointers to the Symbol Table and associated String Table
  // using offsets found earlier. Then SEARCH the symbol table for for
  // the specified function.

  Elf64_Sym *symb_table = (Elf64_Sym *) ((char *)ehdr + symb_offset);
  char *str_table = (char *)((char *)ehdr + str_offset);
  for(int i =0; i<entries;i++){
  // If symbol at position i matches the 'func_name' variable
      // defined at the start of main(), it is the symbol to work on.
      // PRINT data about the found symbol.
      char *symb_name = str_table + symb_table[i].st_name; //symbol at position i
      if(strcmp(symb_name, func_name) == 0){
      printf("Found Function '%s'\n",symb_name);
      printf("- %d symbol index\n", i);
      printf("- 0x%lx value\n", symb_table[i].st_value);
      printf("- %lu size\n",symb_table[i].st_size);
      printf("- %hu section index\n",symb_table[i].st_shndx);

    // CHECK that the symbol table field st_shndx matches the index
      // of the .text section; otherwise the symbol is not a function
      // in the .text section and we should bail out now.
      if( symb_table[i].st_shndx != text_index){// check symbol is actually in the data section
        printf("ERROR: '%s' in section %hd, not in .text section %hd\n",
        func_name,symb_table[i].st_shndx,text_index);
        // UNMAP, CLOSE FD
        munmap(ehdr, size);
        close(fd);
        return 1;
       }

      // CALCULATE the offset of the value into the .text section. The
      // 'value' field of the symbol is its preferred virtual
      // address. The .text section also has a preferred load virtual
      // address. The difference between these two is the offset into
      // the .text section of the mmap()'d file.
    uint64_t text_address = (symb_table[i].st_value-load_address); //offset into the .text section
    printf("- %ld offset in .text of start of function\n",text_address);
    char *bytes_print = text_address + text_sec; //pointer to the bytes to be printed of the loaded function
      // ITERATE: through the bytes of the loaded function
    printf("Bytes of function '%s'", func_name);
    for(int j =0; j<symb_table[i].st_size;j++){

        if (j%8 ==0){
            printf("\n");
            printf("%4x: ", j);
        }
        printf("%02hhx ", bytes_print[j]);

    }
    printf("\n");
    return 0;

    }

    

// Iterated through whole symbol tabel and did not find symbol, error out.
    printf("ERROR: Function '%s' not found\n",func_name);
  // UNMAP, CLOSE FD
    munmap(ehdr, size);
    close(fd);
    return 1;

}
