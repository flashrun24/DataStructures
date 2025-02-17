{
  description = "C++ DataStructures";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      packages.${system}.default = pkgs.stdenv.mkDerivation rec {
        name = "DataStructures";
	version = "0.1";
	nativeBuildInputs = [ pkgs.cmake ];
	src = ./.;
	buildPhase = ''
	  echo "Building cmake..."
	  cmake ..
	  echo "Done building cmake"
	  echo "Building program..."
	  make
	  echo "Done building program"
	'';
	installPhase = ''
	  make install
	'';
      };
    };
  }

