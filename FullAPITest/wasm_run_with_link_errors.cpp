// ---------------------------------------------------------
//  Run a WASM file from SD_MMC (with link error checking)
// ---------------------------------------------------------
bool Wasm::Run(const char* path)
{
    Serial.printf("PSRAM free: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    Serial.printf("PSRAM largest block: %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
    Serial.println(psramFound());

    Serial.printf("[WASM] Loading %s\n", path);

    File f = SD_MMC.open(path, FILE_READ);
    if (!f) {
        Serial.println("[WASM] Failed to open file");
        return false;
    }

    size_t size = f.size();
    uint8_t* wasmBytes = (uint8_t*) malloc(size);
    if (!wasmBytes) {
        Serial.println("[WASM] malloc failed");
        f.close();
        return false;
    }

    f.read(wasmBytes, size);
    f.close();

    IM3Module module;
    M3Result result = m3_ParseModule(env, &module, wasmBytes, size);
    if (result) {
        Serial.printf("[WASM] Parse error: %s\n", result);
        free(wasmBytes);
        return false;
    }

    result = m3_LoadModule(runtime, module);
    if (result) {
        Serial.printf("[WASM] Load error: %s\n", result);
        free(wasmBytes);
        return false;
    }

    // Macro for cleaner link error checking
    #define LINK_FUNCTION(name, sig, func) \
        result = m3_LinkRawFunction(module, "env", name, sig, func); \
        if (result) { \
            Serial.printf("[WASM] Link error for %s: %s\n", name, result); \
        }

    // =========================
    // SCREEN + DRAWING
    // =========================

    LINK_FUNCTION("DrawText", "v(*iiiiiii)", WASM_DrawText);
    LINK_FUNCTION("DrawPixel", "i(iii)", WASM_DrawPixel);
    LINK_FUNCTION("ClearScreen", "i(i)", WASM_ClearScreen);
    LINK_FUNCTION("DrawRect", "i(iiiii)", WASM_DrawRect);
    LINK_FUNCTION("FillRect", "i(iiiii)", WASM_FillRect);
    LINK_FUNCTION("DrawCircle", "i(iiii)", WASM_DrawCircle);
    LINK_FUNCTION("FillCircle", "i(iiii)", WASM_FillCircle);
    LINK_FUNCTION("DrawRaw", "i(*iiiii)", WASM_DrawRaw);

    // =========================
    // TOUCH
    // =========================

    LINK_FUNCTION("PollTouch", "i(*)", WASM_PollTouch);

    // =========================
    // WIFI + NETWORK
    // =========================

    LINK_FUNCTION("ConnectToWiFi", "i(**)", WASM_ConnectToWiFi);
    LINK_FUNCTION("DownloadFile", "i(**)", WASM_DownloadFile);
    LINK_FUNCTION("DownloadApp", "i(*)", WASM_DownloadApp);
    LINK_FUNCTION("CheckManifestUpToDate", "i()", WASM_CheckManifestUpToDate);

    // =========================
    // FILESYSTEM
    // =========================

    LINK_FUNCTION("RecursiveDelete", "i(*)", WASM_RecursiveDelete);
    LINK_FUNCTION("FileExists", "i(*)", WASM_FileExists);
    LINK_FUNCTION("ReadFile", "i(* * i)", WASM_ReadFile);
    LINK_FUNCTION("WriteFile", "i(**)", WASM_WriteFile);
    LINK_FUNCTION("AppendToFile", "i(**)", WASM_AppendToFile);
    LINK_FUNCTION("ListDirectory", "i(*)", WASM_ListDirectory);
    LINK_FUNCTION("CreateDirectory", "i(*)", WASM_CreateDirectory);

    // =========================
    // TIME + DELAY
    // =========================

    LINK_FUNCTION("GetTime", "i()", WASM_GetTime);
    LINK_FUNCTION("Delay", "v(i)", WASM_Delay);

    // =========================
    // RANDOM
    // =========================

    LINK_FUNCTION("Random", "i(ii)", WASM_Random);

    #undef LINK_FUNCTION

    // -----------------------------------------------------
    //  Find and call main()
    // -----------------------------------------------------
    Serial.println("[WASM] Linking complete, searching for main()...");
    
    IM3Function mainFunc;
    result = m3_FindFunction(&mainFunc, runtime, "main");
    if (result) {
        Serial.printf("[WASM] main() not found: %s\n", result);
        free(wasmBytes);
        return false;
    }

    Serial.println("[WASM] Running main()...");
    result = m3_CallV(mainFunc);

    if (result) {
        Serial.printf("[WASM] Runtime error: %s\n", result);
    } else {
        Serial.println("[WASM] main() finished OK");
    }

    free(wasmBytes);

    return result == m3Err_none;
}
