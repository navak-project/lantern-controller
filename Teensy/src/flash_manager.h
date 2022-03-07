void initFlashMem()
{
    // initialize
    if (!SerialFlash.begin(FLASH_CS_PIN))
    {
        while (1)
        {
            Serial.println("Unable to access the SPI Flash chip");
            delay(500);
        }
    }

    // copy loop folders
    
}

void copyFromSD(const char *dir)
{
    File rootdir = SD.open(dir);
    while (1)
    {
        // open a file from the SD card
        Serial.println();
        File f = rootdir.openNextFile();
        if (!f)
            break;
        const char *filename = f.name();
        Serial.print(filename);
        Serial.print(F("    "));
        unsigned long length = f.size();
        Serial.println(length);

        // check if this file is already on the Flash chip
        if (SerialFlash.exists(filename))
        {
            Serial.println(F("  already exists on the Flash chip"));
            SerialFlashFile ff = SerialFlash.open(filename);
            if (ff && ff.size() == f.size())
            {
                Serial.println(F("  size is the same, comparing data..."));
                if (compareFiles(f, ff) == true)
                {
                    Serial.println(F("  files are identical :)"));
                    f.close();
                    ff.close();
                    continue; // advance to next file
                }
                else
                {
                    Serial.println(F("  files are different"));
                }
            }
            else
            {
                Serial.print(F("  size is different, "));
                Serial.print(ff.size());
                Serial.println(F(" bytes"));
            }
            // delete the copy on the Flash chip, if different
            Serial.println(F("  delete file from Flash chip"));
            SerialFlash.remove(filename);
        }

        // create the file on the Flash chip and copy data
        if (SerialFlash.create(filename, length))
        {
            SerialFlashFile ff = SerialFlash.open(filename);
            if (ff)
            {
                Serial.print(F("  copying"));
                // copy data loop
                unsigned long count = 0;
                unsigned char dotcount = 9;
                while (count < length)
                {
                    char buf[256];
                    unsigned int n;
                    n = f.read(buf, 256);
                    ff.write(buf, n);
                    count = count + n;
                    Serial.print(".");
                    if (++dotcount > 100)
                    {
                        Serial.println();
                        dotcount = 0;
                    }
                }
                ff.close();
                if (dotcount > 0)
                    Serial.println();
            }
            else
            {
                Serial.println(F("  error opening freshly created file!"));
            }
        }
        else
        {
            Serial.println(F("  unable to create file"));
        }
        f.close();
    }
    rootdir.close();
    delay(10);
}

bool compareFiles(File &file, SerialFlashFile &ffile)
{
    file.seek(0);
    ffile.seek(0);
    unsigned long count = file.size();
    while (count > 0)
    {
        char buf1[128], buf2[128];
        unsigned long n = count;
        if (n > 128)
            n = 128;
        file.read(buf1, n);
        ffile.read(buf2, n);
        if (memcmp(buf1, buf2, n) != 0)
            return false; // differ
        count = count - n;
    }
    return true; // all data identical
}