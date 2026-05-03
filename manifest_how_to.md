# ```#``` = to **start and end** sections
# ```!``` = **end** of line

-----

# For Additional Assets

# ```N/A``` = No Additonal Assets (only for additional Assets area)
# ```,``` = More than one Additonal Asset (only for additional Assets area)

---------

# **ALWAYS IN THIS ORDER**

*App Name#Description#Version#Download Link#Additional Assets!*


EX:

Clock#App that tells the time#https://DownloadLink.com#N/A!

# **OR**

Clock#App that tells the time#https://DownloadLink.com#https://DownloadLinkForClockFaceImage.png!

# **OR EVEN**

Clock#App that tells the time#https://DownloadLink.com#https://DownloadLinkForClockFaceImage.png,https://DownloadLinkForSoundEffect.wav!


# Download Link format

https://raw.githubusercontent.com/SuperGuy123456/MTOSApps/main/HelloWorldTest/HelloWorldTest.wasm

emcc -O2 ClearScreenTest.cpp -o ClearScreenTest.wasm \
    -s STANDALONE_WASM=1 \
    -s INITIAL_MEMORY=6291456 \
    -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
    -s EXPORTED_FUNCTIONS='["_main"]' \
    -s WASM_ASYNC_COMPILATION=0