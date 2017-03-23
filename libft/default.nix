{ stdenv }:

stdenv.mkDerivation {
	name = "libft";
	src = ./.;

    buildPhase = ''
      make
    '';

    installPhase = ''
        mkdir -p $out/lib
        mkdir -p $out/include

        cp libft.a $out/lib
        cp includes/* $out/include
    '';
}
