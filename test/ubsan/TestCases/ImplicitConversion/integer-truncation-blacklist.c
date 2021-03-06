// FIXME: https://code.google.com/p/address-sanitizer/issues/detail?id=316
// I'm not sure this is actually *that* issue, but this seems oddly similar to the other XFAIL'ed cases.
// XFAIL: android
// UNSUPPORTED: ios

// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation                           -O0 %s -o %t && not %run %t 2>&1 | FileCheck %s --implicit-check-not="implicit conversion"
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation                           -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s --implicit-check-not="implicit conversion"
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation                           -O2 %s -o %t && not %run %t 2>&1 | FileCheck %s --implicit-check-not="implicit conversion"
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation                           -O3 %s -o %t && not %run %t 2>&1 | FileCheck %s --implicit-check-not="implicit conversion"

// RUN: rm -f %tmp
// RUN: echo "[implicit-integer-truncation]" >> %tmp
// RUN: echo "fun:implicitTruncation" >> %tmp
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation -fsanitize-blacklist=%tmp -O0 %s -o %t && not %run %t 2>&1 | not FileCheck %s
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation -fsanitize-blacklist=%tmp -O1 %s -o %t && not %run %t 2>&1 | not FileCheck %s
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation -fsanitize-blacklist=%tmp -O2 %s -o %t && not %run %t 2>&1 | not FileCheck %s
// RUN: %clang -fsanitize=implicit-integer-truncation -fno-sanitize-recover=implicit-integer-truncation -fsanitize-blacklist=%tmp -O3 %s -o %t && not %run %t 2>&1 | not FileCheck %s

unsigned char implicitTruncation(unsigned int argc) {
  return argc; // BOOM
// CHECK: {{.*}}integer-truncation-blacklist.c:[[@LINE-1]]:10: runtime error: implicit conversion from type 'unsigned int' of value 4294967295 (32-bit, unsigned) to type 'unsigned char' changed the value to 255 (8-bit, unsigned)
}

int main(int argc, char **argv) {
  return implicitTruncation(~0U);
}
