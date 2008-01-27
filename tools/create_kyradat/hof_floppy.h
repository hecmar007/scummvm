const ExtractEntry kyra2File1E[] = {
	{ k2SeqplayPakFiles, 0x0002132A, 0x0002134C },
	{ k2SeqplayStrings, 0x00022DF2, 0x000236BA },
	{ k2SeqplaySfxFiles, 0x000236BA, 0x0002382D },
	{ k2SeqplayIntroTracks, 0x0002383A, 0x0002384A },
	{ k2SeqplayFinaleTracks, 0x00023857, 0x00023869 },
	{ k2SeqplaySeqData, 0x000223E0, 0x00022AD4 },
	{ -1, 0, 0 }
};

const ExtractEntry kyra2File1F[] = {
	{ k2SeqplayPakFiles, 0x00020F9D, 0x00020FBF },
	{ k2SeqplayStrings, 0x00022A9C, 0x00023431 },
	{ k2SeqplaySfxFiles, 0x00023431, 0x000235A4 },
	{ k2SeqplayIntroTracks, 0x000235B1, 0x000235C1 },
	{ k2SeqplayFinaleTracks, 0x000235CE, 0x000235E0 },
	{ k2SeqplaySeqData, 0x000223E0, 0x0002277E },
	{ -1, 0, 0 }
};

const ExtractEntry kyra2File1G[] = {
	{ k2SeqplayPakFiles, 0x000211F9, 0x0002121B },
	{ k2SeqplayStrings, 0x00022D30, 0x0002371C },
	{ k2SeqplaySfxFiles, 0x0002371C, 0x0002388F },
	{ k2SeqplayIntroTracks, 0x0002389C, 0x000238AC },
	{ k2SeqplayFinaleTracks, 0x000238B9, 0x000238CB },
	{ k2SeqplaySeqData, 0x0002231E, 0x00022A12 },

	{ -1, 0, 0 }
};

const ExtractEntry kyra2File2E[] = {
	{ k2IngamePakFiles, 0x0035E4E, 0x00362ED },
	{ k2IngameSfxFiles, 0x00034700, 0x00034DF1 },
	{ k2IngameSfxIndex, 0x0002A710, 0x0002AA68 },
	{ k2IngameTracks, 0x0003B2F2, 0x0003B370 },
	{ -1, 0, 0 }
};

const ExtractEntry kyra2File2F[] = {
	{ k2IngamePakFiles, 0x0003AA9C, 0x0003AB1A },
	{ k2IngameSfxFiles, 0x00033E24, 0x00034515 },
	{ k2IngameSfxIndex, 0x000288B0, 0x00028C08 },
	{ k2IngameTracks, 0x0003B2F2, 0x0003B370 },
	{ -1, 0, 0 }
};

const ExtractEntry kyra2File2G[] = {
	{ k2IngamePakFiles, 0x0035626, 0x0035AC5 },
	{ k2IngameSfxFiles, 0x00033ED8, 0x000345C9 },
	{ k2IngameSfxIndex, 0x000288E0, 0x00028C38 },
	{ k2IngameTracks, 0x0003AA8C, 0x0003AB0A },
	{ -1, 0, 0 }
};

const Game kyra2FloppyGames[] = {
	{ kKyra2, EN_ANY, k2FloppyFile1, "9b0f5e57b5a2ed88b5b989cbb402b6c7", kyra2File1E},
	{ kKyra2, FR_FRA, k2FloppyFile1, "df31cc9e37e1cf68df2fdc75ddf2d87b", kyra2File1F},
	{ kKyra2, DE_DEU, k2FloppyFile1, "0ca4f9a1438264a4c63c3218e064ed3b", kyra2File1G},
	{ kKyra2, EN_ANY, k2FloppyFile2, "7c3eadbe5122722cf2e5e1611e19dfb9", kyra2File2E},
	{ kKyra2, FR_FRA, k2FloppyFile2, "fc2c6782778e6c6d5a553d1cb73c98ad", kyra2File2F},
	{ kKyra2, DE_DEU, k2FloppyFile2, "0d9b0eb7b0ad889ec942d74d80dde1bf", kyra2File2G},
	GAME_DUMMY_ENTRY
};
