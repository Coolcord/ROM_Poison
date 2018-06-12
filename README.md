ROM Poison
==========

Easily corrupt ROMs or files in a few clicks.

[![GitHub release](https://img.shields.io/github/release/Coolcord/ROM_Poison.svg)](https://GitHub.com/Coolcord/ROM_Poison/releases)
[![Github all releases](https://img.shields.io/github/downloads/Coolcord/ROM_Poison/total.svg)](https://GitHub.com/Coolcord/ROM_Poison/releases)

# [Download for Windows](https://github.com/Coolcord/ROM_Poison/releases/download/v1.0.0/ROM_Poison.zip)

## About ROM Poison

ROM Poison is designed to be a simple, but powerful, ROM corruptor. Due to
the nature of ROM corruptors, this can be used on any file, but it is
intended to be used with video game ROMs (such as NES, SNES, and N64 games).
It is written in C++11 using the Qt5 libraries, making it multiplatform.

If you're wondering why anyone would want to corrupt a ROM, the answer is that
it can produce interesting and entertaining results. Games and programs can
be made to behave in ways that they were never intended to. Even the most stable
application can be broken with a corruptor.

When designing ROM Poison, I was heavily inspired by the Vinesauce ROM 
Corruptor. However, I was not too fond of the direction that the Vinesauce
ROM Corruptor took. In my opinion, it is too focused on making Youtube/Twitch
fodder, leaving its corruption features rather lacking. To top it off, I
needed something that is multiplatform.

This is where ROM Poison comes in. It focuses solely on corrupting and expands
upon the idea by adding more options and simplifying the process. If a user
wants to corrupt a ROM with ROM Poison, all they need to do is choose which
file to corrupt and where to save the corruption. By default, every time
a user presses "Generate Corruption", a new corruption will be randomly generated.

Ultimately, what ROM Poison does is edits each byte of a binary file. It can do
this in one of 5 ways: adding, subtracting, shifting left, shifting right,
replacing, or randomizing. Randomizing bytes can produce the most interesting
results, which is why it is on by default.

Starting and ending offsets can be set to limit the corruption to a certain area
of a ROM. Setting the "Corrupt every" minimum and maximum values determines the
range of values that the the corruptor will increment before corrupting the next
byte. Setting these to the same value will produce consistent results (assuming
"Random Byte Corruption" is disabled"). These settings can be saved and loaded
later. To automatically load settings when ROM Poison starts, save the settings
profile as "Default.rps"and place it in ROM Poison's "Profiles" folder. Saved
settings that produce consistent results can be distributed to other users and
used as a patch file. These can then be used to create the same corruption
without distributing the ROM.

Like the Vinesauce ROM Corruptor, ROM Poison has "NES CPU Jam Protection". However,
this feature is built-in. When loading a ROM, ROM Poison checks to see if the ROM
is a NES or Famicom ROM. If it is either, the feature will be automatically
enabled. When enabled, ROM Poison will prevent creating invalid assembly commands
that are known to cause the NES to crash or freeze.

If you wish to contact me about the application, or anything of the like,
feel free to send me an email at coolcord24@tutanota.com
