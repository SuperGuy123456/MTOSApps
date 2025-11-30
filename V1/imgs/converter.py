import sys

def convert_text_to_raw(input_file, output_file):
    with open(input_file, "r") as f:
        text = f.read()

    # Split by commas and strip whitespace
    tokens = [t.strip() for t in text.split(",") if t.strip()]

    with open(output_file, "wb") as out:
        for token in tokens:
            # Convert "0xFFFF" style hex string to integer
            value = int(token, 16)

            # Write as 2 bytes, little-endian
            out.write(value.to_bytes(2, byteorder="little"))

    print(f"Converted {len(tokens)} values into {output_file}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python convert_raw.py input.txt output.raw")
    else:
        convert_text_to_raw(sys.argv[1], sys.argv[2])