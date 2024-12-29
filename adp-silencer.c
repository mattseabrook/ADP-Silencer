#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRAME_SIZE 32 // Size of a DTK frame in bytes
#define HEADER_SIZE 4 // Size of the frame header in bytes

void mute_adp(const char *input_file, const char *output_file)
{
    FILE *infile = fopen(input_file, "rb");
    if (!infile)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *outfile = fopen(output_file, "wb");
    if (!outfile)
    {
        perror("Error opening output file");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    uint8_t frame[FRAME_SIZE];
    size_t frame_count = 0;

    printf("Processing frames:\n");
    while (fread(frame, 1, FRAME_SIZE, infile) == FRAME_SIZE)
    {
        frame_count++;

        // Display information about the current frame
        printf("Frame %zu: Header: %02X %02X %02X %02X\n",
               frame_count, frame[0], frame[1], frame[2], frame[3]);

        // Preserve header and mute the rest of the frame
        for (size_t i = HEADER_SIZE; i < FRAME_SIZE; i++)
        {
            frame[i] = 0x00;
        }

        // Write the muted frame to the output file
        if (fwrite(frame, 1, FRAME_SIZE, outfile) != FRAME_SIZE)
        {
            perror("Error writing to output file");
            fclose(infile);
            fclose(outfile);
            exit(EXIT_FAILURE);
        }
    }

    printf("Total frames processed: %zu\n", frame_count);

    fclose(infile);
    fclose(outfile);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input.adp> <output.adp>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    mute_adp(input_file, output_file);

    printf("Muted ADP file written to '%s'\n", output_file);
    return EXIT_SUCCESS;
}