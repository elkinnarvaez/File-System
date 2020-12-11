/*
    References: https://github.com/Luminoid/Simple-File-System
    Based on: Ethan Lee project - CS170: Simple File System
*/

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define MAX_FILENAME_LEN 15
#define MAX_FILE_DESCRIPTOR 32
#define MAX_FILE 64

typedef enum { false, true } bool;

typedef struct{
    /*
        Super block in UNIX-based systems:
            * Number of i-nodes: An i-node contains the file's attributes and a list of pointers to the blocks composing the files.
            * Number of blocks
    */
    // Directory info
    int dir_index;
    int dir_len;

    // Data info
    int data_index;
} super_block;

/* file information */
typedef struct{
    bool used; // whether the file is being used
    char name[MAX_FILENAME_LEN]; // file name
    int size; // file size
    int head; // first data block
    int num_blocks; // number of blocks
    int fd_count; // number of file descriptors using this file
} file_info;

/* file descriptor */
typedef struct{
    bool used; // whether the file descriptor is being used
    char file; // file index
    int offset; // read offset used by fs_read()
} file_descriptor;

/* File system functions */
int make_fs(char *disk_name);
int mount_fs(char *disk_name);
int umount_fs(char *disk_name);
int fs_open(char *name);
int fs_close(int fildes);
int fs_create(char *name);
int fs_delete(char *name);
int fs_read(int fildes, void *buf, size_t nbyte);
int fs_write(int fildes, void *buf, size_t nbyte);
int fs_get_filesize(int fildes);
int fs_lseek(int fildes, off_t offset);
int fs_truncate(int fildes, off_t length);

/* Helper functions */
char find_file(char* name);
int find_free_file_des(char file_index);
int find_free_block(char file_index);
int find_next_block(int current, char file_index);

#endif