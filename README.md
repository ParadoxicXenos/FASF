# FASF
Fast Archival Storage Format is an archival format based around a few core principles:
  
Speed / Liteness  
Portability  
Compression  
Integrity / Redundancy  

# Header/ File Layouts

|Component|Byte Offset|Size (Bytes)|Data Type / Representation|Functional Purpose|
|---------|-----------|------------|--------------------------|------------------|
|Magic ID|0x00|4 Bytes|46 41 53 46 (ASCII: "FASF")|Identifies the file as FASF|
|Original Filetype Identifier|0x04|1 Byte|Hexidecimal Value|Helps FASF restore the correct header|
|Payload Size|0x05|8 Bytes|Unsigned int 64bit|Size of the data payload|
|DATA PAYLOAD|0x0d|Variable|Unsigned char|THE RAW DATA|
