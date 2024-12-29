**Table-of-Contents**
- [Introduction](#introduction)
  - [Use Case(s)](#use-cases)
- [Build](#build)
- [Usage](#usage)
  - [Multi-File](#multi-file)
    - [Windows](#windows)
    - [Linux / Mac](#linux--mac)


# Introduction

This utility is able to carefully "mute" or silence the `*.adp` ADPCM-DTK audio files found on the Nintendo GameCube. It does so by parsing each ADP frame, frame header, and then zero'ing out the subsequent data.

This way, the CHECKSUM adds up and the DVD-ROM images are able to be repackaged.

## Use Case(s)

- Streaming with your own soundtrack
- Some games do not have an Option to silence or adjust background music
- Emulators cannot differentiate between Music and SFX
- Speedrunning Practice
- PracHack / ROMHacking

# Build

Process is straight-forward on any platform, an `x64` Windows Release has been included in this repo, but you could compile to any target you like:

```bash
# Standard build
clang -o3 adp-silencer.exe adp-silencer.c

# Target x64 Windows
clang -o3 adp-silencer.exe adp-silencer.c -static -target x86_64-w64-mingw32
```

# Usage

Simply run the utility against your desired `*.adp` file, and provide a new name for the silenced output file:

```bash
adp-silencer track.adp silenced-track.adp
```

**NOTE**: *The original ADP file must be deleted and your new silenced file renamed to the original name. Please be careful and use a utility like Dolphin to unpack the GameCube DVD's for you*

## Multi-File

If you're lucky, such as I was with Super Monkey Ball, all of the `*.adp` files are in the same directory. Here's how you can use the utility to bulk-silence all of the music:

### Windows

Execute as a Powershell script or copy as a one-liner:

```powershell
# Loop through all .adp files in the current directory
foreach ($file in Get-ChildItem -Filter *.adp) {
    $outputFile = "$($file.BaseName)-silent.adp"
    .\adp-silencer.exe $file.FullName $outputFile
}
```

### Linux / Mac

Same as above, but using the *sh terminal:

```bash
# Loop through all .adp files in the current directory
for file in *.adp; do
    output_file="${file%.adp}-silent.adp"
    ./adp-silencer "$file" "$output_file"
done
```