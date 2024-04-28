{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell rec {
  buildInputs = [
    zig
  ];
}


