for A in ./bin/*; do
	echo -n $A "- "
	$A <$1;
done
