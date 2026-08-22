/*
 * ############################################################################
 * ##                                                                        ##
 * ##                          H E L L O ,   W O R L D                       ##
 * ##                                                                        ##
 * ##     An Inquiry into the Descent of a Sentence, the Machine That         ##
 * ##     Utters It, and the Question of Whether Anything Is Meant By It      ##
 * ##                                                                        ##
 * ##                    A Dissertation in Three Volumes                      ##
 * ##                                                                        ##
 * ##                        Submitted in the file                            ##
 * ##                              hello.c                                    ##
 * ##                                                                        ##
 * ############################################################################
 *
 *
 *                                 ABSTRACT
 *                                 --------
 *
 *  This dissertation examines a program of six lines. The program prints the
 *  string "Hello, World!" to standard output and exits. It computes nothing,
 *  stores nothing, decides nothing, and consumes on the order of a millisecond
 *  of a machine's life.
 *
 *  It is also the single most frequently written program in the history of
 *  the discipline, the first act of authorship of a large fraction of every
 *  programmer alive, and the only sentence the entire profession holds in
 *  common. The thesis advanced here is that these facts are related, and that
 *  the program's emptiness is not incidental to its universality but is
 *  precisely the source of it.
 *
 *  Volume I traces the sentence. Both of its words are old; one is very old.
 *  It follows them from the Pontic-Caspian steppe of the fourth millennium
 *  BCE through Proto-Germanic, Anglo-Saxon England, the Danelaw, the Norman
 *  settlement, the Great Vowel Shift and the printing press, to a Victorian
 *  hunting-cry that was drafted into service by the telephone. It concludes
 *  that the string, read in the oldest available sense of its constituents,
 *  says: is anyone receiving -- to the age of man.
 *
 *  Volume II traces the machine. It follows the language from ALGOL through
 *  the collapse of Multics, the salvage of a PDP-7, the CPL-BCPL-B descent,
 *  the arrival of a byte-addressed machine that forced the invention of the
 *  type system, the 1973 decision to rewrite an operating system in its own
 *  new language, and the fifty subsequent years in which that decision made
 *  C the sediment layer of computing. It closes with a full account of what
 *  physically occurs when this file is compiled and run.
 *
 *  Volume III asks what is being done. It argues that the program is a phatic
 *  utterance in Malinowski's sense and occupies Jakobson's phatic function
 *  exclusively; that as a speech act in Austin's sense it is systematically
 *  infelicitous and works anyway; that it functions epistemically as an
 *  existence proof and a receipt rather than as a message; that its addressee
 *  is a vocative with no referent, placing it nearer to prayer and to the
 *  Pioneer plaque than to conversation; that it is the cleanest available
 *  demonstration of the symbol grounding problem, since it performs a perfect
 *  greeting while containing no representation of greeting; that its social
 *  function is initiatory in van Gennep's sense and its governing metaphor,
 *  per its author, is a hatching; and that its exit -- one utterance and a
 *  status of zero -- constitutes a complete life evaluated on the sole
 *  criterion that nothing went wrong.
 *
 *  No claim is made that any of this improves the program.
 *
 *
 *                             ACKNOWLEDGMENTS
 *                             ---------------
 *
 *  To Brian Kernighan, who wrote the sentence in a Bell Labs memorandum in
 *  1972 and has spent five decades being asked about it.
 *
 *  To Dennis Ritchie (1941-2011), whose obituary was crowded out of the news
 *  cycle by another death that week, and whose work was underneath the
 *  devices on which that other death was mourned.
 *
 *  To the anonymous scribes of the Anglo-Saxon monasteries, who wrote down a
 *  word for the age of man and had no way to know it would end up here.
 *
 *  To the maintainers of every toolchain on which this file has been
 *  compiled without complaint, whose work is visible only when it fails.
 *
 *
 *                            TABLE OF CONTENTS
 *                            -----------------
 *
 *  FRONT MATTER
 *      Abstract
 *      Acknowledgments
 *      Table of Contents
 *      Note on Conventions
 *
 *  VOLUME I. THE DESCENT OF THE SENTENCE
 *      Ch. 1   Proto-Indo-European and the Method of Reconstruction
 *      Ch. 2   Proto-Germanic: The First Great Sound Shift
 *      Ch. 3   Old English: A Fully Inflected Language
 *      Ch. 4   The Norse Contact and the Erosion of Grammar
 *      Ch. 5   1066 and the Making of Middle English
 *      Ch. 6   The Vowel Shift, the Press, and the Freezing of Spelling
 *      Ch. 7   Early Modern to Global: How English Became the Default
 *      Ch. 8   The String Itself: An Etymology of "Hello, World!"
 *
 *  VOLUME II. THE DESCENT OF THE MACHINE
 *      Ch. 9   Prehistory: From Autocodes to ALGOL
 *      Ch. 10  Multics, and the Productive Failure
 *      Ch. 11  Unix on a Cast-Off PDP-7
 *      Ch. 12  CPL, BCPL, B: The Cambridge Line
 *      Ch. 13  The Invention of C
 *      Ch. 14  The 1973 Rewrite: Portability as a Historical Event
 *      Ch. 15  The Book, and the First Appearance of the Phrase
 *      Ch. 16  Standardization: 1978 to 2023
 *      Ch. 17  Descendants, and the ABI as Universal Joint
 *      Ch. 18  Anatomy: What Actually Happens When This File Runs
 *
 *  VOLUME III. ON WHAT IS BEING DONE
 *      Ch. 19  Phatic Communion
 *      Ch. 20  The Program as Speech Act
 *      Ch. 21  The Existence Proof
 *      Ch. 22  The Problem of the Addressee
 *      Ch. 23  Syntax Without Semantics
 *      Ch. 24  Ritual, Initiation, and Natality
 *      Ch. 25  Mortality, and the Meaning of return 0
 *      Ch. 26  Conclusion
 *
 *  APPENDICES
 *      A.  The Sentence in Other Tongues
 *      B.  Chronology
 *      C.  Glossary
 *      D.  On What Has Been Omitted
 *
 *  THE PROGRAM
 *
 *
 *                          NOTE ON CONVENTIONS
 *                          -------------------
 *
 *  Reconstructed forms, which are hypotheses rather than attestations, are
 *  marked with a leading asterisk in the usual way: *wi-ro-. Since this file
 *  is itself a C comment, and since C's block comments do not nest, the
 *  reader is asked to accept that every asterisk here is doing linguistic
 *  work and none of it is doing lexical work.
 *
 *  Dates before roughly 1500 are approximate and contested. Dates in Volume
 *  II are firm to the year where the Bell Labs record is firm and marked as
 *  approximate where it is not.
 *
 *  Where this dissertation says "the string", it means the thirteen
 *  characters "Hello, World!" together with the newline that follows them,
 *  which is fourteen, and the discrepancy is itself discussed in Ch. 25.
 *
 *
 * ############################################################################
 * #                                                                          #
 * #                  VOLUME I. THE DESCENT OF THE SENTENCE                    #
 * #                                                                          #
 * ############################################################################
 *
 * ============================================================================
 *  CHAPTER 1. PROTO-INDO-EUROPEAN AND THE METHOD OF RECONSTRUCTION
 * ============================================================================
 *
 *  1.1  A language known only by its consequences
 *
 *  No one ever wrote down Proto-Indo-European. No inscription, no tablet, no
 *  scratched potsherd. It was spoken, so far as we can tell, between roughly
 *  4500 and 2500 BCE, by a people who left burial mounds and horse bones and
 *  wheel ruts and no text whatsoever.
 *
 *  We nevertheless have dictionaries of it, and grammars, and reconstructed
 *  fables written in it by nineteenth-century philologists showing off. This
 *  is possible because language change is not random. It is regular,
 *  systematic, and in aggregate exceptionless, and regularity can be run
 *  backwards.
 *
 *  1.2  How the trick works
 *
 *  In 1786 Sir William Jones, a judge in Calcutta with a scholarly sideline,
 *  observed that Sanskrit bore to Greek and Latin "a stronger affinity, both
 *  in the roots of verbs and in the forms of grammar, than could possibly
 *  have been produced by accident". Similarity of individual words proves
 *  nothing; anyone can find two words that resemble each other. What Jones
 *  had noticed was systematic correspondence: not that some Sanskrit words
 *  resembled some Latin ones, but that a given Sanskrit sound corresponded to
 *  a given Latin sound across the whole vocabulary, reliably, including in
 *  words too dull to have been borrowed.
 *
 *  Nobody borrows the word for "three". Nobody borrows the pronoun "me".
 *  Nobody borrows their own grammatical endings. When those match, the
 *  languages are not in contact -- they are related.
 *
 *  The comparative method proceeds by assembling such correspondences and
 *  positing the minimal ancestral form from which each attested form could
 *  have descended by regular change. It is inference to the best explanation,
 *  constrained hard by the requirement that the same rule must work
 *  everywhere it applies.
 *
 *  1.3  The laryngeal vindication
 *
 *  The method's credibility rests on a famous episode. In 1879 Ferdinand de
 *  Saussure, then twenty-one, argued on purely internal grounds that PIE must
 *  have contained a class of consonants that had vanished from every known
 *  daughter language, leaving behind only their effects on adjacent vowels.
 *  There was no evidence for them beyond the shape of the hole.
 *
 *  In 1915 Hittite was deciphered. It had been dug out of the ground in
 *  Anatolia, it was older than any Indo-European language previously known,
 *  and in the positions where Saussure's phantom consonants were predicted,
 *  it had a consonant, written with the sign transliterated h. The
 *  reconstruction had predicted a language nobody had read yet.
 *
 *  This is why a linguist will tell you with a straight face what people said
 *  six thousand years ago.
 *
 *  1.4  Where they were
 *
 *  The mainstream account, the Kurgan or steppe hypothesis associated with
 *  Marija Gimbutas and refined since, places the speakers on the
 *  Pontic-Caspian steppe north of the Black and Caspian Seas, and attributes
 *  their expansion to the domesticated horse and the wheeled vehicle.
 *  Vocabulary supports this: PIE has good reconstructed words for horse,
 *  wheel, axle, yoke and wool, and no agreed word for the sea.
 *
 *  Ancient-DNA work since 2015 has strengthened the case considerably, tracing
 *  a large steppe-ancestry migration into Europe in the third millennium BCE.
 *  The principal rival, Colin Renfrew's Anatolian hypothesis, ties the spread
 *  to farming several millennia earlier and retains a minority following.
 *  Nothing in this dissertation turns on the outcome.
 *
 *  1.5  Ablaut, or why English verbs are irregular
 *
 *  PIE roots carried meaning in their consonants and inflected by swapping
 *  the vowel between them -- e-grade, o-grade, zero-grade. This is ablaut, and
 *  it is not decoration; it was load-bearing grammar.
 *
 *  It is still load-bearing in English, five thousand years later, in the
 *  verbs that schoolchildren are told are irregular:
 *
 *      sing / sang / sung
 *      drink / drank / drunk
 *      ride / rode / ridden
 *      give / gave / given
 *
 *  These are not irregular. They are the last speakers of the original system,
 *  surrounded by a crowd of newcomers who all form the past tense by adding a
 *  dental suffix. The strong verbs are old; the weak verbs in -ed are the
 *  innovation. Every child who says "goed" is applying the new rule correctly
 *  and being corrected by a fossil.
 *
 *  1.6  Two roots, held for later
 *
 *  From the reconstructed lexicon this dissertation requires exactly two
 *  items, both unremarkable:
 *
 *      *wi-ro-   "man, freeman, adult male"
 *                Latin vir; Old Irish fer; Lithuanian vyras; Gothic wair;
 *                Old English wer, which survives in English in precisely one
 *                word, werewolf, literally man-wolf, and in the legal term
 *                wergild, the price of a man.
 *
 *      *al-      "to grow, to nourish, to come to maturity"
 *                Latin alere "to feed" (whence aliment, alimony, adult, and
 *                alumnus, one who is nourished); Old English eald "old" and
 *                eldu "age".
 *
 *  Two ordinary agricultural-society words. In Chapter 3 they will be welded
 *  together in a Saxon monastery. In Chapter 8 the result will turn up in a
 *  string literal on a machine in a Bell Labs corridor. The reader is asked
 *  to keep them in view.
 *
 * ============================================================================
 *  CHAPTER 2. PROTO-GERMANIC: THE FIRST GREAT SOUND SHIFT
 * ============================================================================
 *
 *  2.1  The branch
 *
 *  By perhaps 500 BCE a group of PIE speakers had settled the southern
 *  Scandinavian peninsula, Jutland and the North Sea coast, and their dialect
 *  had diverged enough to be called Proto-Germanic. Like its parent it is
 *  unattested; unlike its parent it is close enough to written Gothic, Old
 *  Norse, Old High German and Old English that the reconstruction is tight.
 *
 *  What makes Germanic recognizable at a glance is that it did something
 *  drastic and thorough to its consonants.
 *
 *  2.2  Grimm's Law
 *
 *  Jacob Grimm -- the elder of the brothers, and a professional philologist
 *  whose fairy tales were a side project of the same impulse to collect --
 *  formalized in 1822 a pattern noticed by Rasmus Rask. Every inherited PIE
 *  stop consonant moved, in a chain, one step around a circle:
 *
 *      voiceless stops   ->  voiceless fricatives    p t k  ->  f th h
 *      voiced stops      ->  voiceless stops         b d g  ->  p t k
 *      aspirated stops   ->  voiced stops           bh dh gh ->  b d g
 *
 *  The consequences are visible in any Latin-English word pair that has not
 *  been reborrowed:
 *
 *      Latin pater      English father       (p -> f)
 *      Latin piscis     English fish         (p -> f)
 *      Latin pes/pedis  English foot         (p -> f, d -> t)
 *      Latin tres       English three        (t -> th)
 *      Latin cornu      English horn         (k -> h)
 *      Latin canis      English hound        (k -> h)
 *      Latin genus      English kin          (g -> k)
 *      Latin dentis     English tooth        (d -> t)
 *
 *  Every one of these pairs is a single PIE word that took two routes out of
 *  the steppe and met again in an English dictionary, which is why English
 *  can distinguish paternal from fatherly and canine from houndlike. The
 *  Latinate half of each pair arrived later, by boat and by conquest, and did
 *  not go through the shift.
 *
 *  2.3  Verner's Law, and the rescue of the exceptions
 *
 *  Grimm's Law had a residue of exceptions, which mattered enormously,
 *  because the entire nineteenth-century programme rested on the claim that
 *  sound laws are exceptionless. In 1875 Karl Verner showed that the
 *  exceptions were themselves regular: where the PIE accent had not fallen on
 *  the immediately preceding syllable, the expected voiceless fricative came
 *  out voiced instead.
 *
 *  The residue of that residue is still in the language. The alternation in
 *  was/were, and the one in seethe/sodden, and the one in death/dead, are
 *  Verner's Law preserved in amber. So is the noun-verb pair advice/advise in
 *  its Germanic analogues.
 *
 *  Verner's paper was the decisive moment for the Neogrammarian school, whose
 *  slogan -- sound laws admit no exceptions -- is the reason any of this is a
 *  science rather than a pastime.
 *
 *  2.4  The fixing of stress, and its long fuse
 *
 *  Proto-Germanic then made a change whose consequences take two thousand
 *  years to arrive. PIE stress was mobile: it moved around the word depending
 *  on the grammatical form. Germanic nailed it to the first syllable of the
 *  root and left it there.
 *
 *  Everything after a fixed stress is a downhill slope. Unstressed syllables
 *  reduce; reduced syllables neutralize toward schwa; schwa falls silent. And
 *  in an inflected language, the grammar lives in the endings -- which is to
 *  say the grammar was now standing downhill of the stress.
 *
 *  This is the slow-acting poison. Old English will inherit a full case
 *  system and lose it. The proximate cause will look like the Norse and the
 *  Normans, in Chapters 4 and 5. The distal cause was decided here, before
 *  anyone had crossed the North Sea.
 *
 *  2.5  What else Germanic did
 *
 *  Three further innovations, all still with us:
 *
 *  The dental preterite. Germanic invented a way to form a past tense by
 *  suffixing a dental consonant -- English -ed -- rather than by ablaut. It is
 *  the productive rule to this day: every new verb takes it. Googled. Texted.
 *  Rebased.
 *
 *  The strong/weak adjective distinction. An adjective inflected one way after
 *  a determiner and another way without one. English has lost it entirely;
 *  German retains it and its students suffer accordingly.
 *
 *  A two-tense system. PIE had an elaborate aspect system; Germanic reduced
 *  the finite verb to present and past, and everything else -- future,
 *  perfect, progressive, conditional -- had to be rebuilt later out of
 *  auxiliaries. English will build a great deal later out of auxiliaries.
 *
 *  2.6  The first borrowings
 *
 *  Before the migration to Britain, Germanic speakers were already trading
 *  with Rome, and the loanwords are exactly what trade predicts: wine (vinum),
 *  street (via strata, the paved way), mile (mille passus), pound (pondo),
 *  cheese (caseus), kitchen (coquina), cup (cuppa), and -- from castra, a
 *  military camp -- the -chester, -caster and -cester in Manchester,
 *  Lancaster and Gloucester. The English map is annotated in Latin by the
 *  Roman army.
 *
 *  Also inherited from this period is the compounding habit: Germanic freely
 *  glues nouns together to make new nouns. This is how German gets its long
 *  words, and it is how, in the next chapter, a word for man and a word for
 *  age become a single word for the world.
 */

/*
 * ============================================================================
 *  CHAPTER 3. OLD ENGLISH: A FULLY INFLECTED LANGUAGE
 * ============================================================================
 *
 *  3.1  The settlement
 *
 *  Rome withdrew its garrison from Britain in 410. Within a few decades,
 *  Germanic-speaking groups from across the North Sea -- Angles from the
 *  Danish peninsula, Saxons from the German coast, Jutes from Jutland, and
 *  Frisians who are the closest linguistic relatives English has -- were
 *  arriving in numbers, first as hired soldiers and then as settlers.
 *
 *  Bede, writing in 731, gives an orderly account of invited mercenaries who
 *  turned on their hosts. Archaeology suggests something messier and slower.
 *  What is not in doubt is the linguistic outcome, which is strange: the
 *  Brittonic Celtic spoken by the existing population left almost no mark on
 *  English. A handful of place names, the rivers, the hills -- Avon is simply
 *  the Welsh for river, and Torpenhow Hill is, in three languages laid on top
 *  of each other, Hill-hill-hill-hill. Beyond that, near silence. Languages in
 *  contact normally exchange vocabulary in both directions. This one did not,
 *  and the reason is a matter of ongoing and somewhat uncomfortable debate.
 *
 *  3.2  Four dialects, and the accident of the archive
 *
 *  Old English came in four broad dialects: Northumbrian and Mercian in the
 *  north and midlands, Kentish in the southeast, and West Saxon in the south
 *  and west.
 *
 *  Nearly everything we have is in West Saxon, and this is not because West
 *  Saxon was central. It is because Alfred of Wessex survived the Viking
 *  wars, and because he then did something no other early medieval European
 *  king thought to do: he ran a state translation programme, into the
 *  vernacular, on the grounds that his kingdom's literacy in Latin had
 *  collapsed and something had to be salvaged. Boethius, Gregory, Bede,
 *  Orosius, all into English, some of it by Alfred's own hand.
 *
 *  The dialect of the surviving corpus is therefore an artifact of who won a
 *  war and who then bothered to write things down. This is worth remembering
 *  whenever anyone speaks of what Old English "was".
 *
 *  3.3  The grammar
 *
 *  Old English is not English with odd spelling. It is a different kind of
 *  language, closer in machinery to modern German or Icelandic.
 *
 *  Nouns had three genders, assigned without regard to sense -- wif, "woman",
 *  was neuter -- and declined in five cases: nominative, accusative, genitive,
 *  dative, and a vestigial instrumental. Declension classes were multiple:
 *  a-stems, o-stems, i-stems, u-stems, n-stems, and a set of consonant stems
 *  that survive today as the last irregular plurals in the language. Man/men,
 *  foot/feet, tooth/teeth, goose/geese, mouse/mice and louse/lice are not
 *  irregular either; they are the survivors of a class that formed its plural
 *  by fronting the root vowel under the influence of a following -i- that has
 *  since disappeared. The process is called i-mutation, and it is the reason
 *  the plural is inside the word rather than on the end of it.
 *
 *  Verbs came in seven strong classes, inflecting by ablaut, and three weak
 *  classes, inflecting by the dental suffix. Adjectives agreed with their
 *  nouns in gender, number, case and definiteness. Word order was consequently
 *  free in a way modern English cannot imitate: because the endings carried
 *  the roles, the words could be arranged for emphasis or for meter.
 *
 *  Of the Old English vocabulary, roughly eighty-five percent is gone. What
 *  survives is the part nobody could afford to lose: be, have, do, go, come,
 *  eat, drink, sleep, live, die, love, hate, man, wife, child, house, home,
 *  water, earth, day, night, sun, moon, good, evil, hot, cold, this, that,
 *  the, and, but, if, in, on, under, to. A person cannot construct a sentence
 *  in modern English without using Old English. The Latin and French words are
 *  the furniture; the Old English words are the floor.
 *
 *  3.4  The poetry
 *
 *  Old English verse does not rhyme and does not count syllables. Each line is
 *  two half-lines divided by a pause, with two stressed syllables in each
 *  half, and the alliteration of the stressed syllables binds the halves
 *  together. It is a meter built for a language with fixed initial stress --
 *  which is to say, the poetic form is a direct consequence of the sound
 *  change described in section 2.4.
 *
 *  Its characteristic device is the kenning, a compressed metaphorical
 *  compound used in place of a plain noun: the sea is the whale-road, the
 *  body is the bone-house, the sun is the sky-candle, a ship is the wave-horse.
 *  This is the Germanic compounding habit turned into a literary technique. It
 *  is also, in passing, the same instinct that produces the compound noun in
 *  section 3.6.
 *
 *  Beowulf survives in exactly one manuscript, which was scorched in the
 *  Cotton library fire of 1731 and has been crumbling at the edges ever
 *  since. The margin of survival for the founding poem of English literature
 *  was one bad night.
 *
 *  3.5  Christianization and the second Latin layer
 *
 *  Augustine landed in Kent in 597 and the conversion brought a second wave of
 *  Latin, this time ecclesiastical and scholarly rather than commercial:
 *  bishop, priest, monk, nun, altar, candle, mass, school, verse, and the
 *  Greek-via-Latin church, angel, devil.
 *
 *  It also brought the alphabet. Old English had been written in runes, the
 *  futhorc, well suited to carving and poorly suited to parchment. The
 *  Roman alphabet arrived with the missionaries and took over, retaining two
 *  runes it needed for sounds Latin lacked -- thorn and wynn -- plus eth and
 *  ash. Thorn, the th-rune, survived in English writing into the fifteenth
 *  century, when continental printers who had no thorn in their type cases
 *  substituted the nearest-looking letter, y. This is the entire origin of
 *  "Ye Olde": it was never pronounced ye. It was always the. It is a printing
 *  error that became a decorative style.
 *
 *  3.6  weorold
 *
 *  Now the two roots from section 1.6 arrive.
 *
 *  The Anglo-Saxons required a word for a concept Latin split in two.
 *  Christian Latin had mundus, the created cosmos, and saeculum, the age, the
 *  era, this present time as against eternity. Neither was borrowed. Instead,
 *  in the ordinary Germanic way, two native nouns were compounded:
 *
 *      wer      "man"      ( < PIE *wi-ro- )
 *      +
 *      eld      "age"      ( < PIE *al- )
 *      =
 *      weorold, woruld     "the age of man"
 *
 *  Attested across the corpus, and cognate throughout Germanic: Old Saxon
 *  werold, Old High German weralt (modern German Welt), Old Norse verold
 *  (modern Icelandic verold), Dutch wereld. The compound is older than
 *  English; it is Proto-West-Germanic at least.
 *
 *  The semantics deserve care, because the modern word has drifted a long way
 *  and it is easy to read the drift backwards.
 *
 *  Weorold does not mean the planet. The planet is eorthe. Weorold means the
 *  temporal, human sphere: this age, the span of human existence, the
 *  arrangement of affairs among the living, as distinct from eternity. When
 *  an Old English homilist warns against the weorold, he is not warning
 *  against geology. The sense is preserved in fossilized phrases that still
 *  sound faintly archaic -- worldly goods, this world and the next, world
 *  without end -- every one of which is about time and the human condition
 *  rather than about a globe.
 *
 *  So the second word of the string, in its original and literal sense, names
 *  the age of man: the whole human situation, considered as something a
 *  person is inside of and will leave.
 *
 *  The word for the physical planet was available. It was not the one that
 *  ended up in the string.
 *
 * ============================================================================
 *  CHAPTER 4. THE NORSE CONTACT AND THE EROSION OF GRAMMAR
 * ============================================================================
 *
 *  4.1  793 and after
 *
 *  The raid on Lindisfarne in 793 opens the Viking age in England; what
 *  follows over the next two centuries is not principally raiding but
 *  settlement. By the Treaty of Wedmore the north and east of England was the
 *  Danelaw, under Scandinavian law and full of Scandinavian farmers. The
 *  place names map the settlement precisely: every -by is a Norse farmstead
 *  (Derby, Whitby, Grimsby), every -thorpe an outlying hamlet, every -thwaite
 *  a clearing, every -toft a plot.
 *
 *  4.2  Mutually half-intelligible, which is the dangerous case
 *
 *  Old English and Old Norse were perhaps four or five centuries diverged.
 *  Their roots were largely shared. Their inflections were not.
 *
 *  This is linguistically the most corrosive possible arrangement. Two
 *  languages that share no vocabulary can coexist for centuries; speakers
 *  learn one or the other. Two languages that share everything are one
 *  language. But when the roots match and the endings differ, speakers can
 *  make themselves understood by leaning on the roots and dropping the
 *  endings -- and if enough of the population is doing that, in enough
 *  households, for enough generations, the endings do not come back.
 *
 *  Whether this constitutes creolization is a live argument; some scholars go
 *  as far as calling Middle English a Norse-English creole, which most reject.
 *  What is not in dispute is the timing. The collapse of English inflection
 *  begins in the north, in the Danelaw, and spreads south. The grammar dies
 *  where the Norse were.
 *
 *  4.3  The pronoun theft
 *
 *  Languages borrow nouns easily, verbs readily, adjectives happily. They do
 *  not borrow pronouns. Pronouns are core grammar, learned first, used
 *  constantly, and essentially never replaced from outside.
 *
 *  English replaced its third-person plural pronouns with Norse ones.
 *
 *      they, them, their   <  Old Norse their, theim, theira
 *
 *  The native forms were hie, him, hira, which had become dangerously similar
 *  to the singular he/him/his under the erosion described above, and the Norse
 *  set was adopted to clear the ambiguity. English also took its present
 *  plural of "to be": are is Norse. The verb "to be" is the most frequent verb
 *  in the language and part of its conjugation is a loan.
 *
 *  This is not the profile of casual borrowing. It is the profile of two
 *  populations living in the same houses.
 *
 *  4.4  The doublets
 *
 *  Where both languages kept a word, English often kept both, and split the
 *  meaning:
 *
 *      native (OE)      Norse           the split today
 *      -----------      -----           ---------------
 *      shirt            skirt           two garments
 *      shatter          scatter         two kinds of dispersal
 *      whole            hale            health vs. completeness
 *      no               nay             emphasis
 *      from             fro             only in "to and fro"
 *      rear             raise           two ways to bring up
 *      church           kirk            north and south
 *
 *  The sk- cluster is a reliable Norse fingerprint, since native English sk-
 *  had palatalized to sh-. Sky, skin, skill, skull, scrape, scrub, score,
 *  scowl and the humble egg are all Norse. Caxton, in 1490, records a story of
 *  a merchant in Kent asking for eggys and being told the woman spoke no
 *  French -- she knew the word as eyren, the native form. Two words for egg
 *  were still competing four hundred years after the settlement, and the
 *  Norse one won.
 *
 *  Also Norse: law, and outlaw, and husband, and window (vindauga, wind-eye),
 *  and knife, and die, take, get, give, want, call, cast, and the adjectives
 *  ugly, wrong, weak, ill, happy, odd, loose, low, flat, tight and rotten.
 *
 *  4.5  The consequence for the sentence
 *
 *  Nothing in "Hello, World!" is Norse. What the Norse contribute is the
 *  reason the sentence can be as short as it is: an English that had kept its
 *  case endings would not permit a bare nominative-form noun to stand as a
 *  vocative. Weorold would need to be inflected to be addressed.
 *
 *  Word, in Chapter 22, is going to have to do the work of a vocative with no
 *  marking on it whatsoever. That it can is a consequence of two centuries of
 *  Anglo-Danish farmers not bothering with the ends of words.
 *
 * ============================================================================
 *  CHAPTER 5. 1066 AND THE MAKING OF MIDDLE ENGLISH
 * ============================================================================
 *
 *  5.1  The conquest as a linguistic event
 *
 *  On 14 October 1066, near Hastings, an English king was killed and the
 *  entire ruling class of England was replaced within a generation by
 *  French-speaking Normans. By the Domesday survey of 1086 the English
 *  landholding aristocracy has essentially vanished from the record.
 *
 *  English did not die. It stopped being written.
 *
 *  For roughly three hundred years, England ran on three languages in a
 *  stable and rigid stratification: Latin for the church, the university and
 *  the permanent record; French for the court, the law, the aristocracy and
 *  literature; English for everyone else, spoken, at home, and largely
 *  unwritten. The great majority of the population spoke only the third.
 *
 *  5.2  Grammar off the leash
 *
 *  A written standard is a brake on change. It gives a language a fixed
 *  reference, a conservative clergy of scribes, and a prestige form to be
 *  measured against. English lost all of that at a stroke, at exactly the
 *  moment its inflectional system was already crumbling under the pressures of
 *  Chapters 2 and 4.
 *
 *  What happened in those unwritten centuries is the most rapid grammatical
 *  simplification in the recorded history of a major European language. When
 *  English resurfaces in quantity in the fourteenth century:
 *
 *      -  Grammatical gender is gone. All three of them. Completely.
 *      -  The case system is reduced to a genitive -s and a few pronouns:
 *         the wreckage of five cases is he/him/his and who/whom/whose.
 *      -  Adjective agreement is gone.
 *      -  Verb endings are reduced to the third-person -s and nothing else.
 *      -  The plural is -s, everywhere, on almost everything.
 *
 *  And because the endings could no longer carry the grammar, word order took
 *  the job. English became a rigidly subject-verb-object language, and
 *  prepositions expanded to cover what the dative and instrumental used to do.
 *  The language traded morphology for syntax. It has been paying the syntax
 *  bill ever since, which is why English word order is inflexible and why its
 *  poetry has to work harder than Latin's to rearrange a line.
 *
 *  5.3  Ten thousand French words, and a class system in the lexicon
 *
 *  When English returned to writing it brought the vocabulary of three
 *  centuries of French administration with it. The count is on the order of
 *  ten thousand words, of which perhaps three-quarters are still in use.
 *
 *  They arrived in domains, and the domains are precisely the domains of
 *  power:
 *
 *      government   government, parliament, council, tax, revenue, state,
 *                   sovereign, reign, royal, crown, court, prince, duke,
 *                   baron, servant, peasant
 *      law          justice, judge, jury, evidence, verdict, sentence, prison,
 *                   attorney, felony, crime, accuse, acquit, plaintiff
 *      church       religion, sermon, prayer, clergy, virgin, saint, mercy,
 *                   pity, virtue, vice
 *      war          army, navy, soldier, guard, battle, siege, banner,
 *                   lieutenant, sergeant, enemy, peace
 *      cuisine      dinner, supper, feast, appetite, taste, sauce, boil, fry,
 *                   roast, toast, sugar, salad, mutton, beef, pork, venison
 *      fashion      fashion, dress, gown, robe, lace, embroidery, jewel,
 *                   diamond, ornament, luxury
 *      art          art, beauty, colour, image, design, figure, music, poet,
 *                   romance, story, chapter, paper, pen, volume
 *
 *  The most cited illustration is still the best. The animal in the field is
 *  tended by an English-speaking peasant and keeps its English name; the meat
 *  on the table is served to a French-speaking lord and takes a French one:
 *
 *      cow / beef        (boeuf)
 *      pig / pork        (porc)
 *      sheep / mutton    (mouton)
 *      calf / veal       (veau)
 *      deer / venison    (venaison)
 *
 *  The conquest is legible in a menu.
 *
 *  5.4  Three registers, permanently
 *
 *  The result is the feature that most distinguishes English from its Germanic
 *  siblings: near-synonyms at three social altitudes, native, French and
 *  Latin, available for almost any concept.
 *
 *      ask         question        interrogate
 *      end         finish          conclude
 *      rise        mount           ascend
 *      fear        terror          trepidation
 *      holy        sacred          consecrated
 *      time        age             epoch
 *      fire        flame           conflagration
 *      kingly      royal           regal
 *      help        aid             assistance
 *      hearty      cordial         cardiac
 *
 *  The English word is short, blunt, and emotionally direct. The French word
 *  is formal. The Latin word is technical or elevated. No English speaker is
 *  taught this and every English speaker knows it, which is why plain writing
 *  advice always reduces to the same instruction: prefer the Old English word.
 *
 *  Note where the string sits. World is native, direct, and monosyllabic. The
 *  Latinate options were available -- one could address the mundane sphere, or
 *  the terrestrial globe, or the saeculum. Nobody has ever written a first
 *  program that says "Salutations, Terrestrial Sphere". The register is
 *  chosen, and it is chosen at the bottom, where the plain words are.
 *
 *  5.5  Chaucer, and the accident of which dialect became standard
 *
 *  The English that resurfaced as an official language was not the West Saxon
 *  of the old manuscripts. It was the East Midland dialect, and it became the
 *  standard for reasons that are entirely non-linguistic: it was the dialect
 *  of London, which was the seat of government and trade; of the Chancery,
 *  whose clerks produced a torrent of documents in a consistent house style
 *  from the 1430s; and of Oxford and Cambridge, which drew and returned
 *  students along that corridor.
 *
 *  Chaucer wrote in it, and his choosing to write serious poetry in English at
 *  all -- around 1387, for the Canterbury Tales -- was a deliberate act of
 *  literary politics at a moment when a court poet would default to French.
 *
 *  Standard English is therefore the dialect of a particular trade route. It
 *  is not more logical, more original or more correct than the Northumbrian
 *  that lost. It is simply the one that was spoken where the paperwork was.
 */

/*
 * ============================================================================
 *  CHAPTER 6. THE VOWEL SHIFT, THE PRESS, AND THE FREEZING OF SPELLING
 * ============================================================================
 *
 *  6.1  The Great Vowel Shift
 *
 *  Between roughly 1400 and 1700, every long vowel in English moved.
 *
 *  Not some. Every one. The long high vowels broke into diphthongs, and every
 *  other long vowel rose one step to fill the space vacated above it. It was a
 *  chain shift, it took perhaps three hundred years, and nobody at any point
 *  noticed it happening or wrote a word of complaint about it.
 *
 *      Middle English            Modern English
 *      ---------------           --------------
 *      long i   (as in "machine")   ->  the diphthong in "bite"
 *      long e   (as in "hey")       ->  the vowel in "meet"
 *      long a   (as in "father")    ->  the vowel in "name"
 *      long u   (as in "boot")      ->  the diphthong in "house"
 *      long o   (as in "boat")      ->  the vowel in "moon"
 *
 *  Chaucer's "lyf" was said roughly like modern "leaf"; four generations later
 *  it was "life". His "name" rhymed with modern "calm-uh"; his "hous" was
 *  "hoose"; his "mete" was "mate". Read aloud correctly, Chaucer sounds
 *  markedly less like Shakespeare than Shakespeare sounds like us -- the shift
 *  falls between them.
 *
 *  Causes are disputed and probably plural: population movement into London
 *  after the plague years, dialect contact, prestige imitation, and simple
 *  chain-shift mechanics in which one movement leaves a gap that pulls the
 *  next vowel up after it. No cause is agreed. The fact is not in doubt.
 *
 *  6.2  Caxton, 1476
 *
 *  William Caxton set up a printing press at Westminster in 1476, which is to
 *  say: roughly a quarter of the way through the shift.
 *
 *  Printing standardizes spelling. It has to -- a compositor needs a
 *  convention, an edition needs internal consistency, and a market wants a
 *  book that looks like other books. Caxton's own practice was inconsistent
 *  and his assistants were Flemish, which is why English has the gh in ghost
 *  (from Flemish gheest, where the h was doing real work in Dutch and none in
 *  English), and why that h then spread by analogy into ghastly and aghast.
 *
 *  But the convention, once set, outlived the sounds it was recording.
 *
 *  6.3  Why English spelling is like this
 *
 *  English orthography is a photograph of a language in motion, taken with a
 *  long exposure, at the worst possible moment, by several photographers who
 *  disagreed.
 *
 *  Every silent letter is a fossil with a date:
 *
 *      knight, knee, know      the k was pronounced until c. 1600
 *      gnaw, gnat              the g was pronounced
 *      write, wrong, wren      the w was pronounced
 *      night, light, thought   the gh was a real consonant, still audible in
 *                              Scots "nicht" and German "Nacht"
 *      name, time, made        the final e was a syllable
 *      half, calm, walk        the l was pronounced
 *
 *  And then a second layer of damage was applied deliberately. Renaissance
 *  scholars, believing spelling should display etymology, inserted letters
 *  into words that had never had them:
 *
 *      dette      ->  debt        (to show Latin debitum)
 *      doute      ->  doubt       (Latin dubitare)
 *      samon      ->  salmon      (Latin salmo)
 *      receit     ->  receipt     (Latin recepta)
 *      iland      ->  island      (by false analogy with isle; the word is
 *                                 native and never had an s in its life)
 *
 *  These are not sound changes. They are corrections applied to a language
 *  that did not need correcting, by men showing their Latin, and English
 *  children have been paying for them for four hundred years.
 *
 *  6.4  What this does to "hello"
 *
 *  The relevance to the string is indirect but real. English spelling froze
 *  in the fifteenth and sixteenth centuries. Hello does not enter the written
 *  language until the nineteenth. It therefore arrives after the freeze, with
 *  no fossil layer, no silent letters and no etymological vandalism, spelled
 *  exactly as it sounds.
 *
 *  It is one of the very few words in the sentence-initial position of English
 *  writing that a foreign learner can spell correctly on first hearing. This
 *  is not a coincidence of the tutorial; it is a consequence of the word being
 *  young. The oldest word in the string is unspellable from its sound. The
 *  newest is transparent.
 *
 * ============================================================================
 *  CHAPTER 7. EARLY MODERN TO GLOBAL: HOW ENGLISH BECAME THE DEFAULT
 * ============================================================================
 *
 *  7.1  The inkhorn controversy
 *
 *  The sixteenth century poured Latin and Greek into English directly, by the
 *  bucket, on the argument that the vernacular was too poor to carry serious
 *  thought. Thousands of words entered in a few decades. Many stuck --
 *  education, dedicate, encyclopedia, skeleton, atmosphere, capsule,
 *  expectation. Many did not: adnichilate, illecebrous, deruncinate,
 *  suppeditate, eximious.
 *
 *  There was a backlash. The critics called the imports inkhorn terms, after
 *  the writer's inkwell, and John Cheke wrote in 1557 that English should be
 *  "written clean and pure, unmixed and unmangled with borrowing of other
 *  tongues", which is a sentence containing three words of French and Latin
 *  origin and demonstrates the difficulty.
 *
 *  The argument was never settled. It was inherited. Every subsequent debate
 *  about plain English, every style guide that says prefer the short word,
 *  every complaint about jargon, is the inkhorn controversy still running.
 *
 *  7.2  Shakespeare, and a language briefly without rules
 *
 *  Early Modern English had no dictionary, no academy, and no settled view on
 *  what a word could be. A writer could convert a noun to a verb at will,
 *  compound freely, and coin without apology.
 *
 *  Shakespeare is credited with the first attestation of somewhere between
 *  one and two thousand words, though the figure is inflated by the fact that
 *  his corpus is large, popular and exhaustively indexed, so he catches
 *  credit for coinages that were merely in the air. What is not inflated is
 *  the grammatical freedom on display. He verbs nouns constantly -- to dog, to
 *  season, to elbow, to out-Herod -- and the language let him.
 *
 *  Also in this period: do-support arrives, giving English its peculiar
 *  auxiliary in questions and negatives (he goes / does he go / he does not
 *  go, where every other Germanic language simply inverts); the second-person
 *  distinction collapses, with the plural/formal you swallowing the singular
 *  thou entirely, leaving English alone among major European languages with
 *  no T-V distinction and a permanent regional itch to reinvent a plural you
 *  (y'all, youse, you guys, yinz); and the King James Bible of 1611 fixes a
 *  cadence in the ear of every subsequent English writer, largely by being
 *  deliberately archaic even in its own day.
 *
 *  7.3  Johnson, and the invention of the authority
 *
 *  Samuel Johnson published his Dictionary in 1755, alone, in nine years, with
 *  six assistants doing the copying, against the forty academicians of the
 *  Academie francaise who took forty years. He defined 42,773 words and
 *  illustrated them with 114,000 quotations, and he did something in the
 *  preface that matters more than the definitions: he abandoned the project of
 *  fixing the language.
 *
 *  He had begun intending to arrest change and preserve purity. He finished
 *  writing that to imagine a language can be embalmed is the "dream of a
 *  poet"; that words are the daughters of earth while things are the sons of
 *  heaven; and that the lexicographer's job is to record, not to legislate.
 *
 *  Nobody has ever fully accepted this, which is why prescriptivism remains a
 *  going concern. The specific rules most confidently enforced today are
 *  largely eighteenth-century inventions with no basis in the language's
 *  history: the ban on the split infinitive (invented by analogy with Latin,
 *  where the infinitive is one word and cannot be split), the ban on ending a
 *  sentence with a preposition (Dryden, 1672, also from Latin), and the
 *  insistence on "it is I" (imported from Latin case grammar into a language
 *  that had already lost its cases). All three are foreign rules applied to a
 *  language that never had them.
 *
 *  7.4  Divergence, empire, and reach
 *
 *  Noah Webster's American dictionaries from 1806 deliberately diverged the
 *  spelling on nationalist grounds -- colour to color, centre to center,
 *  defence to defense -- and largely succeeded, which is why the two standards
 *  differ in exactly the ways one man decided they should.
 *
 *  Empire then carried English to every continent, producing in each place a
 *  local English with its own history rather than a copy of the metropolitan
 *  one. Indian English, Nigerian English, Singaporean English, Caribbean
 *  Englishes, and the creoles are not degraded versions of anything. There are
 *  now considerably more second-language speakers of English than native ones,
 *  and the centre of gravity has moved accordingly.
 *
 *  7.5  Why the program speaks English
 *
 *  This chapter exists to answer one question, which is usually not asked
 *  because the answer looks obvious and is not.
 *
 *  There is no technical reason a first program should print English. The
 *  machine has no preference. Character encoding was, for the first decades,
 *  actively hostile to anything else -- ASCII was standardized in 1963 with
 *  128 code points and no accented characters at all, which is itself a
 *  political artifact rather than a technical necessity, and which imposed a
 *  real cost on every other language in the world for the following thirty
 *  years until Unicode.
 *
 *  The reason is a chain of historical accidents with no linguistic content:
 *  the war-time and post-war computing programmes were British and American;
 *  the transistor, the integrated circuit, the commercial mainframe and the
 *  minicomputer were American; the standards bodies were American; the network
 *  was built with American defence money; the keyboards, the encodings, the
 *  manuals and the compiler error messages were English. FORTRAN, COBOL,
 *  ALGOL, LISP, BASIC, C -- all in English keywords, and the keywords are not
 *  translated because a program is not a text and its identifiers are not
 *  words.
 *
 *  So the sentence in this file is in English for the same reason the airline
 *  pilot over Frankfurt speaks English to the tower: not because of anything
 *  about the language, but because a standard had to be picked and history
 *  had already picked one.
 *
 *  Volume I has traced a sentence back six thousand years. This section is the
 *  reminder that the last four hundred of those years are why the reader can
 *  read it, and that this is contingency rather than merit.
 *
 * ============================================================================
 *  CHAPTER 8. THE STRING ITSELF: AN ETYMOLOGY OF "HELLO, WORLD!"
 * ============================================================================
 *
 *  8.1  hello: a noise before it was a word
 *
 *  Hello is young, and it did not begin as a greeting.
 *
 *  It belongs to a scattered family of shouts -- hollo, holla, halloo, hallo,
 *  hillo, hullo -- attested from the late Middle Ages onward, whose function
 *  was not to greet but to hail. One used them to attract the attention of
 *  someone at a distance, to urge on hunting hounds, to summon a ferryman
 *  across water, to stop a person in the street, or to express surprise.
 *
 *  The family is probably related to Old High German hala, hola, the
 *  imperative of a verb meaning to fetch, used specifically for hailing a
 *  ferryman. French has the cognate hola, and the English forms may be
 *  reinforced from there.
 *
 *  Two points about this ancestry deserve emphasis, because both are
 *  load-bearing in Volume III.
 *
 *  First, hello is not a word in the ordinary sense. It has no referent, no
 *  propositional content, and no truth conditions. It is a noise that has been
 *  admitted to the dictionary. One cannot say what it means, only what it
 *  does.
 *
 *  Second, what it does is establish contact at a distance from someone whose
 *  presence has not been confirmed. That is its whole original function.
 *  One does not halloo at a person standing beside them.
 *
 *  8.2  The telephone, and Edison against Bell
 *
 *  The transformation of a hailing-cry into the default English greeting was
 *  caused by a machine, and the record is unusually clear about it.
 *
 *  When the telephone arrived in the late 1870s there was no convention for
 *  addressing a person you could not see, had not approached, and could not
 *  confirm was present. Existing greetings all presuppose bodily co-presence.
 *  Something was needed for the new situation, and the new situation was
 *  precisely the old situation of the hailing-cry: contact at a distance with
 *  an unconfirmed party.
 *
 *  Alexander Graham Bell favoured "Ahoy" -- a nautical hail, on the same
 *  reasoning -- and used it personally for the rest of his life.
 *
 *  Thomas Edison favoured "Hello". In an often-quoted 1877 letter to the
 *  president of the Central District and Printing Telegraph Company, he
 *  argued that no bell was needed on the instrument, because "Hello" could be
 *  heard from ten to twenty feet away.
 *
 *  Edison's version went into the early exchange manuals and the training of
 *  operators. The first telephone directory, from New Haven in 1878, includes
 *  instructions on how to open a call. Exchange operators were known as
 *  "hello girls" for decades. And a word that had been a shout, marginal in
 *  polite usage, became within a single generation the standard English
 *  greeting in every context, telephonic or not.
 *
 *  Register this carefully. The most common greeting in the most widely spoken
 *  language on earth is a piece of nineteenth-century telecommunications
 *  jargon, standardized to solve the problem of addressing an interlocutor
 *  whose presence at the far end of a wire could not be otherwise verified.
 *
 *  8.3  world: recapitulation
 *
 *  From Chapters 1 and 3, in full:
 *
 *      PIE *wi-ro-  "man"        +  PIE *al-  "grow, age"
 *          |                            |
 *      PGmc *weraz                  PGmc *aldiz
 *          |                            |
 *          +------------ *weraldiz -----+
 *                            |
 *                    OE weorold, woruld      "the age of man"
 *                            |
 *                     ME world, worlde
 *                            |
 *                       Mod. world
 *
 *  Sense development: the span of human existence, then the present age as
 *  opposed to eternity, then the sphere of human affairs, then all people,
 *  then -- late, and last -- the physical planet. The modern default sense is
 *  the newest one in the list.
 *
 *  8.4  The punctuation
 *
 *  The comma separates a vocative from the utterance addressed to it, which is
 *  the same comma as in "Goodbye, Mr. Chips" and "Let's eat, Grandma". Its
 *  presence is what makes the second word an addressee rather than an object.
 *  Without it -- "Hello World" -- the phrase reads as a name, and the sentence
 *  becomes an announcement rather than a greeting. The entire argument of
 *  Chapter 22 depends on a comma.
 *
 *  The exclamation point is not original. Kernighan's is the flat lowercase:
 *
 *      hello, world
 *
 *  The capitals and the exclamation mark are a later, cheerier redaction, and
 *  their spread is a textbook case of what happens to any text copied for
 *  fifty years by people who have never seen the original. The version in this
 *  file is the redacted one, because that is the form the reader will encounter
 *  everywhere else, and the discrepancy is noted here rather than silently
 *  corrected.
 *
 *  8.5  The full gloss
 *
 *  Reading each element in the oldest sense available to it:
 *
 *      Hello       a hailing-cry, whose function is to determine whether an
 *                  unconfirmed party at a distance is receiving; domesticated
 *                  into a greeting, within living memory, by the telephone
 *
 *      ,           vocative separator; marks what follows as the addressee
 *
 *      World       *wi-ro- + *al-, "the age of man": the human situation
 *                  considered as a span of time one is inside of
 *
 *      !           an intensifier of no fixed meaning, added later by copyists
 *
 *      \n          relinquishment of the line; see Chapter 25
 *
 *  Which is to say, in the plainest available English:
 *
 *          Is anyone receiving? -- to the age of man.
 *
 *  It has been saying that, unchanged, on every architecture built since 1972.
 *
 *  END OF VOLUME I.
 */

/*
 * ############################################################################
 * #                                                                          #
 * #                  VOLUME II. THE DESCENT OF THE MACHINE                    #
 * #                                                                          #
 * ############################################################################
 *
 * ============================================================================
 *  CHAPTER 9. PREHISTORY: FROM AUTOCODES TO ALGOL
 * ============================================================================
 *
 *  9.1  The problem programming languages solve
 *
 *  A stored-program computer executes numbers. The numbers denote operations,
 *  and a human being can write them directly, and for the first several years
 *  human beings did exactly that: toggling switches, punching tape, working in
 *  octal. It is possible. It does not scale, and more importantly it does not
 *  travel -- a program written in the numbers of one machine is meaningless on
 *  another.
 *
 *  The entire history in this volume is the history of that second problem.
 *  Every step is an attempt to write a program once and run it in more than
 *  one place, and each step buys portability at the cost of control, and each
 *  step is resisted at the time by people who point out, correctly, what is
 *  being given up.
 *
 *  9.2  Assemblers and autocodes (1949-1955)
 *
 *  The first move is symbolic assembly: write ADD rather than the opcode, let
 *  a program do the encoding, and let it also compute the addresses so that
 *  inserting an instruction does not require renumbering everything after it.
 *  This last point is the one that mattered most in practice and it is the one
 *  least remembered.
 *
 *  Alick Glennie's Autocode for the Manchester Mark 1, around 1952, is
 *  generally counted the first compiled language. Grace Hopper's A-0 system at
 *  UNIVAC dates from 1951 and her team's later work led to FLOW-MATIC and
 *  thence to COBOL. Hopper's recorded difficulty was not technical: it was
 *  persuading colleagues that a machine could usefully write its own programs
 *  at all, an idea widely regarded as unserious.
 *
 *  9.3  FORTRAN (1957)
 *
 *  John Backus's team at IBM shipped FORTRAN for the 704 in 1957 with an
 *  explicit and commercially necessary promise: the compiler would produce
 *  machine code as good as a competent human's. This was not a selling point
 *  in the modern sense; it was the precondition for anyone using it at all.
 *  The optimizer was consequently the most sophisticated program yet written,
 *  and it worked, and the promise was kept.
 *
 *  FORTRAN made the case that a high-level language need not be slow, which
 *  is the case C would have to make again fifteen years later against
 *  assembly, and which Java, then Python, then everything else would have to
 *  make again in turn.
 *
 *  9.4  ALGOL 60, and the shape of everything after
 *
 *  ALGOL 60 was designed by an international committee -- unusually, one that
 *  produced something good -- and it is the most influential language almost
 *  nobody ever used in production. Tony Hoare's judgment is the standard one:
 *  that it was an improvement on nearly all of its successors.
 *
 *  What it contributed is now so ordinary that its absence is unimaginable:
 *
 *      -  Block structure, with begin and end, and lexical scope
 *      -  Nested functions, and recursion as a first-class expectation
 *      -  Formal parameters, and local variables that are actually local
 *      -  A formal syntax specification, in what became Backus-Naur Form,
 *         so that the language was defined by a grammar rather than by an
 *         implementation
 *
 *  That last item is the quiet revolution. Before ALGOL, a language was
 *  whatever its compiler accepted. After ALGOL, a language could be a
 *  document, and an implementation could be wrong about it.
 *
 *  9.5  The descent
 *
 *  Everything in the following chapters is downstream of ALGOL:
 *
 *      ALGOL 60  ->  CPL  ->  BCPL  ->  B  ->  C  ->  C++, Java, C#, Go, Rust
 *                 ->  Simula 67 (objects)  ->  Smalltalk, C++
 *                 ->  Pascal  ->  Modula, Ada
 *
 *  The braces in this file are ALGOL's begin and end, shortened. The scoping
 *  rules are ALGOL's. The fact that main is a function with parameters and a
 *  return value is ALGOL's. The reader who wants to see what C would have
 *  looked like without ALGOL should look at FORTRAN 66, which had no local
 *  variables, no recursion and no block structure, and in which this program
 *  would still be perfectly writable and would look nothing like this.
 *
 * ============================================================================
 *  CHAPTER 10. MULTICS, AND THE PRODUCTIVE FAILURE
 * ============================================================================
 *
 *  10.1  The ambition
 *
 *  In 1964 MIT's Project MAC, General Electric and Bell Telephone
 *  Laboratories began Multics: the Multiplexed Information and Computing
 *  Service. The goal was a computing utility -- a machine that ran
 *  continuously, served many users at once, and sold computation the way the
 *  power company sold electricity. In 1964 this was a genuinely radical
 *  proposition; the normal relationship between a person and a computer was
 *  to submit a deck of cards and come back tomorrow.
 *
 *  Multics was to be secure by design with hardware-enforced protection rings;
 *  to treat the file system and memory as a single segmented address space;
 *  to support dynamic linking so that programs loaded code on demand; to
 *  survive hardware reconfiguration without rebooting; and to be written in a
 *  high-level language rather than assembly.
 *
 *  Almost all of this was eventually achieved. Multics ran in production until
 *  the year 2000. It is not a failed system.
 *
 *  10.2  The failure that mattered
 *
 *  It was, however, enormously late, and enormously large, and on the hardware
 *  of the middle 1960s it was slow. Bell Labs was funding a research project
 *  whose delivery date kept receding, and in 1969 Bell Labs withdrew.
 *
 *  This left a small group of researchers in New Jersey in an unusual state.
 *  They had spent five years thinking hard about what an operating system
 *  should be. They had watched, at close range, exactly how such a project
 *  fails. They now had no operating system, no project, and -- decisively -- no
 *  management interest in their starting another one.
 *
 *  Every artifact in the rest of this volume follows from that combination.
 *  The Unix design is legible as a set of corrections to Multics written by
 *  people who had loved it: keep the good ideas, and make each of them small.
 *
 *  10.3  What was kept, and what was cut
 *
 *      Multics idea               Unix version
 *      ------------               ------------
 *      hierarchical file system   kept, simplified
 *      the shell as a program     kept, and made replaceable
 *      device-independent I/O     kept, and radicalized: everything is a file
 *      written in a high-level    kept, but only after the language had to be
 *      language (PL/I)            invented, because PL/I was too big
 *      segmented memory as the    dropped
 *      unified address space
 *      dynamic linking            dropped, for a decade
 *      protection rings           reduced to two: kernel and user
 *      access control lists       reduced to nine permission bits
 *
 *  The pattern is consistent. Where Multics generalizes, Unix picks the
 *  smallest version that covers the common case and lets the user compose the
 *  rest. Nine bits instead of an ACL is a real loss of expressiveness and it
 *  fits in a byte and it can be read at a glance, and that trade -- expressive
 *  power for something a person can hold in their head -- is the Unix
 *  aesthetic in a single decision.
 *
 * ============================================================================
 *  CHAPTER 11. UNIX ON A CAST-OFF PDP-7
 * ============================================================================
 *
 *  11.1  A borrowed machine
 *
 *  Ken Thompson found a PDP-7 in a corner, a machine already obsolete when it
 *  was bought, with 8K words of memory and no serious users. On it, in
 *  assembly, over the course of 1969, he wrote a file system, a process
 *  scheduler, a small set of utilities, and a shell.
 *
 *  The often-repeated account is that he did much of it in three weeks in the
 *  summer while his wife was away visiting family with their newborn: roughly
 *  a week each for the editor, the assembler, and the kernel. Thompson has
 *  confirmed the general shape of the story. The motivating application was
 *  Space Travel, a simulation game he had written for Multics and wanted to
 *  keep playing.
 *
 *  Brian Kernighan suggested the name, as a pun on Multics -- Unics, one of
 *  everything where Multics had many -- and it became Unix.
 *
 *  11.2  Everything is a file
 *
 *  The central design decision is a piece of aggressive simplification. In
 *  Unix, an ordinary file, a directory, a terminal, a tape drive, a printer, a
 *  pipe between two programs, and later a network socket, are all reached
 *  through the same small set of operations: open, read, write, close.
 *
 *  The consequence is that a program written to read from a file will read
 *  from a terminal, a tape, or another program's output, without knowing the
 *  difference and without being modified. A program that writes to standard
 *  output does not know whether it is writing to a screen, a file, a printer
 *  or a socket.
 *
 *  This program does not know either. Chapter 18 will make the point
 *  concretely: this file contains no information about where its output goes,
 *  and it works anyway, and that is a design decision made in New Jersey in
 *  1969.
 *
 *  11.3  The pipe
 *
 *  Doug McIlroy had argued since 1964 that programs should couple like garden
 *  hose segments. Thompson implemented pipes in 1973, reportedly in one
 *  evening, and then spent the night rewriting the utilities to use them.
 *
 *  A pipe makes composition the default. It means a tool need not anticipate
 *  its uses, because the user can supply the missing half. McIlroy's summary,
 *  from the Bell System Technical Journal of 1978, remains the clearest
 *  statement of the philosophy: write programs that do one thing and do it
 *  well; write programs to work together; write programs to handle text
 *  streams, because that is a universal interface.
 *
 *  The third clause is why the output of this program is a string of bytes
 *  rather than a structured object, and why it can be piped into anything, and
 *  why fifty years of tooling still assumes it can.
 *
 *  11.4  Why it spread
 *
 *  A 1956 antitrust consent decree barred AT&T from entering the computer
 *  business. Bell Labs therefore could not sell Unix. It licensed it to
 *  universities for a nominal fee, with source code.
 *
 *  This was a legal constraint, not a philosophy. Its effect was that an
 *  entire generation of computer science students learned operating systems by
 *  reading a real one -- John Lions's line-by-line commentary on Version 6,
 *  from 1976, was so widely photocopied after AT&T restricted it that it
 *  became the most illegally reproduced document in the field -- and then
 *  graduated and rebuilt what they knew wherever they went.
 *
 *  Unix propagated because an antitrust ruling forced its owner to give it
 *  away to exactly the population most likely to spread it.
 *
 * ============================================================================
 *  CHAPTER 12. CPL, BCPL, B: THE CAMBRIDGE LINE
 * ============================================================================
 *
 *  12.1  The problem with assembly
 *
 *  Unix on the PDP-7 was written in assembly, which meant Unix was a PDP-7
 *  program. Moving it meant rewriting it. Thompson wanted a language.
 *
 *  12.2  CPL (1963)
 *
 *  The Combined Programming Language was a joint project of Cambridge and the
 *  University of London Institute of Computer Science, with Christopher
 *  Strachey involved. It was an ALGOL descendant of considerable ambition,
 *  intended for scientific and commercial work alike, and it was so large that
 *  a full implementation was never really achieved.
 *
 *  It is remembered almost entirely for what was carved out of it.
 *
 *  12.3  BCPL (1967)
 *
 *  Martin Richards, at Cambridge, wrote Basic CPL: CPL with everything
 *  difficult removed, designed specifically to be easy to port and to compile
 *  in a small machine. Its defining decision is that it has exactly one data
 *  type, the machine word, and the programmer is responsible for knowing what
 *  any given word represents.
 *
 *  BCPL contributed to this file, directly and by descent:
 *
 *      -  Braces for compound statements
 *      -  The compile-and-link-and-run structure
 *      -  A tiny portable runtime
 *      -  The comment convention beginning with two slashes, which BCPL had,
 *         which B dropped, which C++ reintroduced, and which C standardized
 *         only in 1999, thirty-two years later
 *
 *  And one more item of specific relevance: the first published program in
 *  Richards's BCPL documentation prints a greeting.
 *
 *  12.4  B (1969)
 *
 *  Thompson adapted BCPL to the PDP-7, cutting further to fit: shorter
 *  keywords, a smaller syntax, an interpreter-based implementation at first.
 *  Ritchie contributed. The result was B.
 *
 *  B remained typeless. Every value was a machine word, and the same bits were
 *  an integer, a character, or an address depending entirely on what the
 *  programmer did with them. Character strings were packed several to a word
 *  and unpacked by arithmetic.
 *
 *  This is defensible on a word-addressed machine. Real programs were written
 *  in it. It also has an obvious ceiling, and the ceiling arrived with new
 *  hardware.
 *
 * ============================================================================
 *  CHAPTER 13. THE INVENTION OF C
 * ============================================================================
 *
 *  13.1  The PDP-11 forces the issue (1970)
 *
 *  In 1970 the group acquired a PDP-11. It addressed bytes.
 *
 *  A language in which every value is one word cannot describe a machine in
 *  which values are emphatically not all one word. There was no way in B to
 *  say: this is a character, that is a sixteen-bit integer, this other thing
 *  is the address of a structure whose second field is itself a pointer.
 *  Character handling in B on a byte-addressed machine meant hand-written
 *  packing and unpacking, and the resulting code was both slow and wrong in
 *  interesting ways.
 *
 *  13.2  What Ritchie added
 *
 *  Between 1971 and 1973 Dennis Ritchie added, roughly in this order:
 *
 *  Types. char, int, float, double, and the arithmetic conversions between
 *  them. This is the change that makes the language a different language.
 *
 *  Pointers as a distinct type, rather than as integers that happen to be used
 *  as addresses. A pointer in C knows what it points at, which is what makes
 *  pointer arithmetic scale by the size of the target type.
 *
 *  Structures. Aggregate types with named members, and a syntax for reaching
 *  through a pointer to a member. This is what made it possible to describe
 *  the kernel's data structures in the language rather than in comments.
 *
 *  Arrays defined in terms of pointers. The rule is that an array name in an
 *  expression decays to a pointer to its first element, and that subscripting
 *  is defined as pointer arithmetic:
 *
 *      a[i]   is defined as   *(a + i)
 *
 *  From which it follows, since addition commutes, that i[a] is also legal and
 *  means the same thing. This is not a joke in the standard; it is a
 *  consequence of the definition, and it compiles.
 *
 *  This single rule is either the language's most elegant economy or its most
 *  expensive mistake, and which one it is depends entirely on the decade in
 *  which the reader learned it. It gives C its extraordinary directness about
 *  memory. It also means an array does not know its own length, that passing
 *  an array to a function passes an address, and that the bounds check has to
 *  live in the programmer's head. The security history of the following fifty
 *  years is substantially a history of that check not being there.
 *
 *  The preprocessor. A separate, textual, typeless macro layer bolted on in
 *  front of the compiler. It is not part of the language proper, it does not
 *  respect scope or types, and it is the reason the first line of the program
 *  in this file is not a statement.
 *
 *  13.3  Undefined behaviour as a design position
 *
 *  C's standard describes a large class of programs as having undefined
 *  behaviour: signed overflow, dereferencing past the end of an object, data
 *  races, and a long list besides. The standard imposes no requirement
 *  whatsoever on what happens.
 *
 *  This was not carelessness. It was the deliberate refusal to make every
 *  implementation pay, in every program, for a check that a correct program
 *  does not need. In 1972, on a machine with 24K of core, that trade was
 *  simply correct.
 *
 *  Its modern consequences are more uncomfortable, because optimizing
 *  compilers reason forward from the assumption that undefined behaviour does
 *  not occur, and will therefore delete a programmer's check on the grounds
 *  that the condition it tests could only be reached by a route the standard
 *  says cannot happen. The language did not change; the compilers got clever
 *  enough to take it at its word.
 *
 *  This file contains no undefined behaviour. It is one of the few things
 *  about it that can be stated with total confidence.
 *
 *  13.4  The naming
 *
 *  The intermediate version was called NB, for New B. C is simply the next
 *  letter after B, and B was named after BCPL, and BCPL was named for being a
 *  basic CPL. The most consequential programming language in history is named
 *  by taking the second letter of the alphabet and incrementing it.
 *
 *  The obvious next question was answered in 1983 by Bjarne Stroustrup, who
 *  named his extension C++ using C's own increment operator, thereby making
 *  the joke that the language is C, incremented -- and, as critics noted at
 *  once, that the expression returns the old value.
 *
 * ============================================================================
 *  CHAPTER 14. THE 1973 REWRITE: PORTABILITY AS A HISTORICAL EVENT
 * ============================================================================
 *
 *  14.1  The decision
 *
 *  In 1973, Thompson and Ritchie rewrote the Unix kernel in C.
 *
 *  It is difficult now to convey how strange this was. An operating system was
 *  understood to be the one program that must be written in assembly. It
 *  touches the hardware; it manages memory; it handles interrupts; it has no
 *  runtime beneath it to depend on. Writing it in a high-level language was
 *  widely regarded as either impossible or an obvious waste of the machine.
 *
 *  The rewrite cost something. The C kernel was reportedly some 30 percent
 *  larger and correspondingly slower than the assembly version.
 *
 *  14.2  What it bought
 *
 *  In 1977 and 1978, Steve Johnson and Dennis Ritchie ported Unix to the
 *  Interdata 8/32 -- a machine architecturally unlike the PDP-11. Most of the
 *  system moved by recompilation. What had to be rewritten was the small part
 *  that genuinely depended on the hardware.
 *
 *  This had never been done. Before it, an operating system was a thing built
 *  for a machine, and buying different hardware meant starting over, which in
 *  turn meant the hardware vendor owned the software and therefore owned the
 *  customer. After it, an operating system was a thing that could be moved by
 *  writing a compiler back end.
 *
 *  Everything follows from this: the workstation market, the ability of
 *  universities to run the same system on whatever they could afford, the
 *  eventual commoditization of hardware, the fact that a program can be
 *  written once and compiled for a phone and a server and a satellite. The
 *  30 percent was the best trade in the history of the field.
 *
 *  14.3  The compounding
 *
 *  From that point the loop closes on itself. C makes Unix portable; Unix
 *  carries C to every institution that adopts it; the students who learn on it
 *  write their next system in C; and every new architecture arrives with a C
 *  compiler as its first order of business, because without one it cannot run
 *  anything.
 *
 *  Fifty years later, a new processor design is not considered usable until it
 *  has a C compiler, and the reason is still the decision made in 1973.
 */

/*
 * ============================================================================
 *  CHAPTER 15. THE BOOK, AND THE FIRST APPEARANCE OF THE PHRASE
 * ============================================================================
 *
 *  15.1  The 1972 memorandum
 *
 *  The earliest known appearance of the phrase is in Brian Kernighan's
 *  internal Bell Labs document "A Tutorial Introduction to the Language B",
 *  from 1972. It appears again in his 1974 "Programming in C: A Tutorial",
 *  which circulated widely inside the Labs and out of it.
 *
 *  The pedagogical argument for opening with it is stated plainly in the later
 *  book and has never been improved on: the barrier to learning a new language
 *  is not the language, it is the apparatus around it. Before a student can
 *  write anything, they must create a file, compile it, link it, load it, run
 *  it, and find where the output went. Any of those steps can fail in ways the
 *  language cannot explain. The only sane approach is to get the smallest
 *  possible program through the entire apparatus first, and worry about the
 *  language afterwards.
 *
 *  The first program is therefore not a lesson in C. It is a test of
 *  everything except C.
 *
 *  15.2  The chick
 *
 *  Asked repeatedly over five decades where the phrase came from, Kernighan
 *  has offered the same recollection: he believes it came from a cartoon of a
 *  newly hatched chick, standing next to its broken shell, saying "Hello,
 *  world!"
 *
 *  He has said he cannot now find the cartoon and cannot be certain. The
 *  attribution is a memory, not a citation, and it is offered here as one.
 *
 *  It is nevertheless the single most important fact in this dissertation, and
 *  Chapter 24 is built on it. The canonical first program of the discipline is
 *  named after a birth announcement. Whatever else the sentence is doing, its
 *  author's own account of it is that it is spoken by something that has just
 *  come into existence, to a world it has just entered and cannot yet perceive.
 *
 *  15.3  K&R (1978)
 *
 *  "The C Programming Language", by Brian W. Kernighan and Dennis M. Ritchie,
 *  Prentice-Hall, 1978. 228 pages. Second edition 1988, for ANSI C, 272 pages.
 *
 *  The book is the specification and the tutorial and the reference at once,
 *  and it is written with a compression that has not been matched in the
 *  field. It fixed the phrase permanently: it is on the first page of the
 *  first chapter, it is the first thing the reader is told to type, and every
 *  language documentation written since has copied the convention without
 *  necessarily knowing where it came from.
 *
 *  The original, from that page, with its original punctuation:
 *
 *      main()
 *      {
 *          printf("hello, world\n");
 *      }
 *
 *  Note what is absent by modern standards: no include of the header, no
 *  return type on main, no return statement, no parameter list. All of these
 *  were legal in 1978 and the first two are now errors or warnings. The
 *  canonical program does not compile cleanly under the standard the language
 *  eventually acquired, which is a fair summary of what standardization does
 *  to a living practice.
 *
 * ============================================================================
 *  CHAPTER 16. STANDARDIZATION: 1978 TO 2023
 * ============================================================================
 *
 *  16.1  The chronology
 *
 *      1978   K&R C. The specification is a book. Ambiguities are resolved by
 *             asking what the PDP-11 compiler does.
 *
 *      1989   ANSI C, X3.159-1989, known universally as C89. The committee
 *             X3J11 worked for six years. The central additions: function
 *             prototypes, borrowed from C++, so that a compiler can check
 *             arguments against parameters; the const and volatile qualifiers;
 *             a standardized library, which had previously been whatever the
 *             vendor shipped; and the codification of the preprocessor.
 *
 *      1990   ISO/IEC 9899:1990, C90. The same document under an international
 *             number. This is why the same language is called C89 by Americans
 *             and C90 by everyone else.
 *
 *      1999   C99. Comments beginning with two slashes, thirty-two years after
 *             BCPL had them. Declarations permitted anywhere in a block rather
 *             than only at the top. inline. long long. A boolean type, in a
 *             header, spelled awkwardly, because the obvious name had been
 *             taken by half the world's existing code. Variable-length arrays,
 *             which were made optional again in C11 after implementers
 *             objected. Designated initializers. Complex numbers, which almost
 *             nobody uses.
 *
 *      2011   C11. A memory model, and threads, and atomics -- the language
 *             finally acknowledging in its own text that more than one thing
 *             happens at a time. Anonymous structures and unions. Static
 *             assertions. An optional set of bounds-checked library functions
 *             that industry largely declined to adopt.
 *
 *      2017   C17 (published 2018). Defect corrections only. No new features.
 *             Deliberately, and admirably, boring.
 *
 *      2023   C23. constexpr. typeof. nullptr, with an actual type. Binary
 *             literals. Attributes in the C++ syntax. And the removal of the
 *             old K&R function declaration style, which had been deprecated
 *             for thirty-four years -- so the program printed in section 15.3
 *             is now, at last, formally not C.
 *
 *  16.2  What standardization did to the file in front of you
 *
 *  The six lines at the bottom of this file are shaped by that history and
 *  would have been written differently in each era:
 *
 *      #include <stdio.h>     Not needed in 1978, when printf was simply
 *                             assumed to exist. Required from C89, because a
 *                             call to a variadic function without a visible
 *                             prototype is undefined behaviour.
 *
 *      int main(void)         In 1978: main(). The explicit int is required
 *                             since C99, which removed implicit int. The
 *                             (void) rather than () says the function takes no
 *                             arguments; the empty parentheses in C mean
 *                             something subtly different and worse, namely
 *                             that the parameters are unspecified.
 *
 *      return 0;              Optional in main since C99, which specifies that
 *                             falling off the end of main returns 0. Written
 *                             out here anyway, because the alternative is to
 *                             rely on a rule most readers do not know.
 *
 *  16.3  The remarkable thing
 *
 *  The program at the bottom of this file would compile, unmodified, on a
 *  compiler from 1990, and produce the same output. Code written in 1978
 *  requires two small edits to compile today, both mechanical.
 *
 *  Fifty years of backwards compatibility, across every architecture the
 *  industry has produced, is an achievement without much precedent in
 *  engineering. It is also, precisely, the reason the language cannot fix its
 *  known defects: every one of them is load-bearing somewhere.
 *
 * ============================================================================
 *  CHAPTER 17. DESCENDANTS, AND THE ABI AS UNIVERSAL JOINT
 * ============================================================================
 *
 *  17.1  The syntactic family
 *
 *  C's surface syntax -- braces for blocks, semicolons as terminators,
 *  parenthesized conditions, the same operator set, the same precedence
 *  mistakes -- was inherited by C++, Objective-C, Java, C#, JavaScript, PHP,
 *  Perl, Go, Swift, D, and Rust, among others. A substantial majority of all
 *  code written today is written in a language whose punctuation was decided
 *  in New Jersey in 1972 for reasons that were partly about what fitted on a
 *  Teletype keyboard.
 *
 *  This includes the mistakes. The precedence of the bitwise operators is
 *  lower than that of the comparison operators, so that a bitwise test needs
 *  parentheses; Ritchie acknowledged this was wrong and explained that by the
 *  time it was noticed there were already several hundred thousand lines of
 *  code depending on it. The rule is now in a dozen languages, faithfully
 *  copied, along with the bug reports it generates.
 *
 *  17.2  The deeper inheritance: the ABI
 *
 *  More important than the syntax is the calling convention.
 *
 *  When two pieces of software written in different languages, by different
 *  people, compiled by different compilers, need to call each other, they need
 *  to agree on where arguments go, who cleans up the stack, how a return value
 *  comes back, and how a name is spelled in the object file. There is no
 *  neutral standard for this. What exists instead is the C ABI for each
 *  platform.
 *
 *  Python's extension interface is C. Java's native interface is C. Rust's
 *  foreign function interface is C. Go's cgo is C. Every language's binding to
 *  every operating system is C. The kernel's system call interface is
 *  described in C. When two languages that share nothing need to speak, they
 *  agree to speak C, in the same way that two pilots who share no language
 *  agree to speak English -- and for the same kind of reason, which is not
 *  merit but incumbency.
 *
 *  17.3  The sediment
 *
 *  As of this writing: the Linux kernel is C. The Windows kernel is C and C++.
 *  Every BSD is C. The C standard libraries are C. SQLite, PostgreSQL, MySQL,
 *  Redis are C. OpenSSL is C. Nginx is C. FFmpeg is C. Git is C. The reference
 *  implementations of Python, Ruby, PHP, Perl and Lua are C. The JVM is C++
 *  over a C substrate. Every device driver in general use is C.
 *
 *  The languages designed to replace C are, with few exceptions, implemented
 *  in C or in C++, bootstrapped from a C compiler, and linked against a C
 *  runtime. Replacement in this field does not mean removal; it means adding a
 *  layer. The sediment stays.
 *
 * ============================================================================
 *  CHAPTER 18. ANATOMY: WHAT ACTUALLY HAPPENS WHEN THIS FILE RUNS
 * ============================================================================
 *
 *  This chapter exists to support the argument of Chapter 21, which claims
 *  that the program is an existence proof. The claim is only as good as the
 *  inventory of what must exist. Here is the inventory.
 *
 *  18.1  Translation phases
 *
 *  The standard specifies eight phases of translation, in order, as if each
 *  completed before the next began. Real compilers fuse them and are required
 *  only to behave as if they had not.
 *
 *      1.  Physical source characters are mapped to the source character set.
 *          Trigraphs are replaced -- a feature added for keyboards that lacked
 *          braces, and removed in C23, having caused more confusion in its
 *          lifetime than it ever resolved.
 *      2.  Backslash-newline pairs are spliced, so a line can be continued.
 *      3.  The source is decomposed into preprocessing tokens and whitespace.
 *          Comments -- including, notably, all two thousand lines of this one --
 *          are replaced by a single space each. Everything above this line
 *          ceases to exist at phase 3.
 *      4.  Preprocessing directives are executed and macros expanded. The
 *          #include is resolved here: the compiler locates stdio.h and
 *          textually inserts it.
 *      5.  Escape sequences in character constants and string literals are
 *          converted. The two characters backslash and n become the single
 *          newline character.
 *      6.  Adjacent string literals are concatenated.
 *      7.  Tokens are syntactically and semantically analysed and translated.
 *          This is what most people mean by compilation.
 *      8.  External references are resolved and the program image is formed.
 *          This is linking.
 *
 *  18.2  What the header brings
 *
 *  stdio.h does not contain printf. It contains a declaration of printf: the
 *  promise that a function of that name exists somewhere, takes a
 *  null-terminated format string followed by an unspecified number of further
 *  arguments, and returns an int.
 *
 *  This matters for a specific reason. printf is variadic, and the calling
 *  convention for variadic functions differs from the ordinary one on many
 *  platforms. Without a visible prototype the compiler cannot know how to
 *  arrange the call. This is why omitting the include is not a stylistic
 *  lapse but a genuine defect, and why the 1978 version in section 15.3 is
 *  not merely old-fashioned but formally undefined under every standard since.
 *
 *  On a typical system the header expands to several hundred to several
 *  thousand lines. The six-line program is, after phase 4, considerably
 *  larger than the six lines suggest.
 *
 *  18.3  The string
 *
 *  The literal "Hello, World!\n" becomes fourteen bytes of read-only data in
 *  the compiled object -- thirteen visible characters plus the newline -- and
 *  a fifteenth zero byte terminating it.
 *
 *  That terminating zero is Ritchie's, and it is a consequential decision.
 *  BCPL and B stored a length; C stores a sentinel. The sentinel costs one
 *  byte instead of a word, which mattered enormously in 1972, and it means a
 *  string can be pointed into at any position and remain a valid string, which
 *  is genuinely elegant. It also means that determining a string's length
 *  requires walking it, that every string operation is O(n), and that any
 *  operation which loses the terminator runs off the end of the object into
 *  whatever is next. A large fraction of the memory-safety vulnerabilities of
 *  the last four decades trace to that one byte.
 *
 *  The bytes themselves are ASCII, standardized in 1963, which is why the
 *  capital H is 0x48 and the exclamation point is 0x21, and why for thirty
 *  years the rest of the world's writing systems were second-class on every
 *  machine.
 *
 *  18.4  The call
 *
 *  main is called by the C runtime startup code, conventionally crt0, which is
 *  linked in automatically and which nobody reads. Before main runs, that code
 *  has set up the stack, arranged argc and argv, initialized the standard
 *  streams, and run any static constructors.
 *
 *  printf then does the following: parses the format string looking for
 *  conversion specifications, finds none, and copies the bytes into a buffer
 *  belonging to the stdout stream.
 *
 *  18.5  Buffering, and why the newline is not decorative
 *
 *  stdout is line-buffered when attached to a terminal and fully buffered
 *  otherwise -- typically in blocks of four or eight kilobytes. This is a
 *  performance decision: a system call is expensive relative to a copy, so the
 *  library batches.
 *
 *  The newline terminating the string therefore does real work. On a terminal
 *  it triggers the flush, and the text appears immediately. Without it, the
 *  output would sit in the buffer until the program exited and the runtime
 *  flushed the streams during exit -- which in this program is roughly a
 *  microsecond later, so it would still appear, and the beginner would never
 *  learn the lesson.
 *
 *  The lesson matters in the case where the program does not exit cleanly. A
 *  program that crashes after printing to a fully-buffered stream loses its
 *  output entirely, which is why the last thing printed before a crash is so
 *  often not the last thing that was executed, and why a generation of
 *  programmers has debugged by adding a flush.
 *
 *  18.6  The descent into the kernel
 *
 *  The flush calls write, which is not a function in the ordinary sense but a
 *  thin wrapper that places a system call number and arguments in registers
 *  and executes a trap instruction. The processor switches privilege level and
 *  transfers control to the kernel's handler.
 *
 *  The kernel validates the file descriptor, follows it to an open file
 *  description, finds the terminal driver, and hands the bytes to it. Control
 *  returns to user space with a count.
 *
 *  18.7  The rest of the way
 *
 *  From there the bytes traverse, on a typical modern desktop: a pseudo-
 *  terminal pair; the line discipline; the shell that is the terminal's child;
 *  a terminal emulator, which parses the byte stream for control sequences
 *  descended from the DEC VT100 of 1978 and lays out the remainder into a
 *  glyph grid; a font rasterizer, which resolves each character to a glyph in
 *  a typeface and renders it with hinting and antialiasing; a compositor; a
 *  graphics driver; a display controller; and a panel, where a specific number
 *  of liquid crystal cells change state and photons leave the surface.
 *
 *  Some of those photons enter an eye. The retina transduces them, the optic
 *  nerve carries the signal, the visual cortex assembles it, and the language
 *  areas of a human brain -- running a language traced in Volume I -- resolve
 *  the shapes into a greeting.
 *
 *  18.8  The count
 *
 *  Between the H in this file and the H on the screen there stand, on a
 *  conservative accounting: a preprocessor, a compiler front end, an
 *  optimizer, a back end, an assembler, a linker, a loader, a C runtime, a
 *  standard library, a kernel, a device driver, a terminal emulator, a font
 *  engine, a compositor, a display driver, and hardware at every level from
 *  the instruction decoder to the panel. Tens of thousands of person-years.
 *  Hundreds of institutions. Five decades.
 *
 *  Every one of them must work. Any one of them failing produces nothing.
 *
 *  This is the inventory Chapter 21 requires.
 *
 *  END OF VOLUME II.
 */

/*
 * ############################################################################
 * #                                                                          #
 * #                    VOLUME III. ON WHAT IS BEING DONE                      #
 * #                                                                          #
 * ############################################################################
 *
 * ============================================================================
 *  CHAPTER 19. PHATIC COMMUNION
 * ============================================================================
 *
 *  19.1  The observation that starts everything
 *
 *  The first program a person writes does not compute.
 *
 *  This deserves to be sat with rather than passed over. Of everything a
 *  machine can be made to do -- arithmetic, storage, comparison, iteration,
 *  decision -- the act the discipline has universally settled on teaching
 *  first is none of them. It is greeting.
 *
 *  A first program could add two numbers. It could print the alphabet. It
 *  could compute a factorial, which would at least demonstrate something about
 *  the machine's nature. Instead, before we teach the machine to think, we
 *  teach it to say hello.
 *
 *  19.2  Malinowski, 1923
 *
 *  Bronislaw Malinowski, working among the Trobriand Islanders, needed a term
 *  for a class of utterance his existing theory of meaning could not handle:
 *  speech in which no information is exchanged, no question answered and no
 *  instruction given, and which is nevertheless obligatory and constant.
 *  Remarks about the weather. Enquiries after health from someone who does not
 *  want the answer. Greetings.
 *
 *  He called it phatic communion, from the Greek for utterance, and defined it
 *  as speech in which ties of union are created by a mere exchange of words.
 *  Its function is not to transmit content. Its function is to establish and
 *  maintain the channel, and thereby the relationship.
 *
 *  Roman Jakobson later formalized this in his six functions of language,
 *  where the phatic function is the one oriented toward the channel of contact
 *  itself, as distinct from the referential function oriented toward the
 *  subject matter. Jakobson's own example of pure phatic speech is telephone
 *  talk: "Hello, can you hear me?"
 *
 *  He chose the telephone, and by Chapter 8 the reader knows why that is not
 *  a coincidence.
 *
 *  19.3  hello as the limiting case
 *
 *  Hello is the purest phatic token in English. It has no referent. It cannot
 *  be true or false. It cannot be translated so much as substituted. A
 *  dictionary defining it must resort to describing its use, because there is
 *  nothing else to describe.
 *
 *  Its entire content is: a channel exists, and I am at this end of it.
 *
 *  19.4  The thesis
 *
 *  From which the central claim of this volume follows directly.
 *
 *  "Hello, World!" is not a trivial program with trivial content. It is a
 *  program whose content is deliberately, structurally empty, because its
 *  subject is not any state of affairs but the channel itself.
 *
 *  This is why it cannot be improved by making it say something more
 *  interesting. A first program that printed a fact would be a worse first
 *  program, because the fact would compete for the reader's attention with the
 *  only thing actually being demonstrated, which is that the apparatus
 *  connects at all. Emptiness is the design requirement.
 *
 *  And it explains the otherwise odd universality. The novice printing
 *  "Hello, World!"; the network engineer sending an ICMP echo request to
 *  8.8.8.8; the radio operator saying "radio check"; the person on a bad line
 *  saying "are you still there" -- all four are performing the same speech act
 *  with the same content, which is none. The tutorial's first program belongs
 *  to a genre older than computing, and the genre is: finding out whether the
 *  line is open.
 *
 * ============================================================================
 *  CHAPTER 20. THE PROGRAM AS SPEECH ACT
 * ============================================================================
 *
 *  20.1  Austin
 *
 *  J. L. Austin's How to Do Things with Words (1962) begins from the
 *  observation that a great many utterances are not descriptions at all. "I
 *  promise", "I name this ship", "I apologize", "I do" -- these do not report
 *  a state of affairs. They perform an act. Austin called them performatives,
 *  and noted that they cannot be true or false; they can only succeed or fail,
 *  and he called the conditions of success felicity conditions.
 *
 *  A greeting is a performative. Saying hello does not describe a greeting; it
 *  constitutes one.
 *
 *  20.2  The felicity conditions of a greeting
 *
 *  Searle's later analysis gives a greeting roughly the following
 *  requirements. A speaker exists and is a party to the encounter. An
 *  addressee exists and is present. The speaker has just encountered or is
 *  re-establishing contact with the addressee. The speaker intends the
 *  utterance to be recognized as an acknowledgment. And the addressee is in a
 *  position to recognize it.
 *
 *  Now audit the program.
 *
 *      Speaker exists                     Contested. See Chapter 23.
 *      Addressee exists                   No. See Chapter 22.
 *      Addressee is present               Unknowable, and unchecked.
 *      Speaker intends recognition        No. There is no intention anywhere
 *                                         in the process.
 *      Addressee can recognize it         Possibly nobody is watching. The
 *                                         program neither knows nor can find
 *                                         out.
 *
 *  By Austin's criteria the utterance is not merely infelicitous. It fails on
 *  every condition simultaneously. Austin has a category for this -- the
 *  misfire, where the act is purported but not achieved -- and by the letter
 *  of the theory this is a paradigm case.
 *
 *  20.3  And yet
 *
 *  It works.
 *
 *  Every programmer who has run it reports being greeted. The feeling is not
 *  hedged or ironic; it is the reason the moment is remembered decades later.
 *  A theory that classifies the single most successful greeting in the history
 *  of the species as a misfire has a problem, and the problem is not with the
 *  program.
 *
 *  20.4  Where the theory bends
 *
 *  Two repairs are available and both are instructive.
 *
 *  The first: the speaker is not the program but the programmer, displaced in
 *  time. On this reading the machine is a medium and not an agent, the
 *  utterance was authored by a person and merely delivered by the process, and
 *  the felicity conditions are satisfied by the author. This is clean, and it
 *  is how one would treat a letter or a recording. It has the awkward
 *  consequence that the beginner who runs the tutorial program is being
 *  greeted, across five decades, by Brian Kernighan.
 *
 *  The second: felicity is in the uptake. Austin himself makes securing uptake
 *  part of the act. If a competent speaker of English recognizes the utterance
 *  as a greeting -- and they do, universally, without effort -- then the act
 *  has been performed, and the absence of anything corresponding to intention
 *  on the utterer's side is simply not a fact the addressee has access to.
 *
 *  The second repair is the more interesting one, because it concedes that
 *  greeting is something conferred by the recipient rather than possessed by
 *  the speaker. Chapter 23 returns to this.
 *
 * ============================================================================
 *  CHAPTER 21. THE EXISTENCE PROOF
 * ============================================================================
 *
 *  21.1  The receipt
 *
 *  Chapter 18 inventoried what must be true for fourteen bytes to reach a
 *  screen: preprocessor, compiler, optimizer, assembler, linker, loader,
 *  runtime, library, kernel, driver, emulator, font engine, compositor,
 *  hardware. Tens of thousands of person-years across five decades and
 *  hundreds of institutions.
 *
 *  Any single failure in that chain produces nothing at all. The output is
 *  binary in the strictest sense: either the whole tower is standing or the
 *  screen is blank.
 *
 *  Therefore: the string is not the message. The string is a receipt. What is
 *  actually being asserted, when "Hello, World!" appears, is that an
 *  enormous inherited apparatus is, at this moment, on this machine, in this
 *  configuration, load-bearing.
 *
 *  21.2  Why it cannot be replaced by something more useful
 *
 *  This explains the program's persistence against every attempt to improve
 *  it, and there have been many. The improvements always fail for the same
 *  reason: a program that computes something can fail in two distinguishable
 *  ways -- the apparatus is broken, or the computation is wrong -- and the
 *  beginner cannot tell which. The diagnostic value comes precisely from
 *  having nothing to get wrong.
 *
 *  It is the smallest possible question that still requires the entire system
 *  to answer. That is a rare and valuable property and it is purchased with
 *  triviality.
 *
 *  21.3  The genre
 *
 *  The program belongs to a family of artifacts whose purpose is to
 *  demonstrate that a channel works by sending something with no content:
 *
 *      the ICMP echo request         are you reachable
 *      the radio check               is my transmitter working
 *      the test pattern              is the signal intact
 *      the tapping on a microphone   is this on
 *      the "test" email to oneself   does the account send
 *      the smoke test                does the thing turn on
 *
 *  In every case the content is chosen to be maximally uninformative so that
 *  its arrival carries the entire message. McLuhan's formula is usually quoted
 *  as an aphorism about mass media; here it is a literal and exact description
 *  of the engineering. The medium is the message, because the message has been
 *  deliberately emptied so that only the medium remains.
 *
 *  21.4  The epistemic status
 *
 *  Strictly, the program proves less than it appears to. It establishes that
 *  the apparatus worked once, for one trivial path, on one machine, at one
 *  moment. It does not establish that the compiler is correct, that the
 *  library is sound, or that anything larger will work. It is an existence
 *  proof of the weakest possible kind.
 *
 *  This is worth stating because the field has an enduring weakness for
 *  exactly this error at larger scales -- the demo that proves the path
 *  through the system that the demo takes, and nothing else. The first program
 *  is the honest version, because it makes no claim beyond what it shows.
 *  Every subsequent test in a career is a more elaborate version of it, and
 *  most of them claim more than they establish.
 *
 * ============================================================================
 *  CHAPTER 22. THE PROBLEM OF THE ADDRESSEE
 * ============================================================================
 *
 *  22.1  The comma
 *
 *  As established in section 8.4, the comma makes the second word a vocative.
 *  The program does not announce a world; it addresses one.
 *
 *  This raises a question the phrase's ubiquity has worn smooth: who,
 *  precisely, is being addressed?
 *
 *  22.2  The candidates, and their failure
 *
 *  Not the user. The program has no representation of a user. It does not
 *  check whether anyone is logged in, does not query the terminal, does not
 *  branch on whether output is going to a screen or to a file or to a process
 *  that will discard it. If the output is redirected to /dev/null the program
 *  behaves identically and reports success.
 *
 *  Not the terminal. The terminal is a conduit, and the program does not know
 *  it exists. See section 11.2: not knowing is the entire design.
 *
 *  Not the programmer. They wrote it. One does not greet oneself.
 *
 *  Not the machine. The greeting passes through the machine; it is not
 *  directed at it.
 *
 *  22.3  A vocative without a referent
 *
 *  What remains is that the addressee is exactly what the word says: the
 *  world. Which is to say, everything not the speaker. The largest possible
 *  vocative, and therefore -- because a vocative that excludes nothing
 *  selects nothing -- arguably not a vocative at all.
 *
 *  And recall from Chapter 3 what the word originally meant. Not the planet.
 *  The age of man: the human situation, the whole arrangement of affairs among
 *  the living. The program addresses the human condition, in the general case,
 *  from inside a process that will not survive the sentence.
 *
 *  22.4  No channel for a reply
 *
 *  The structural feature that most distinguishes this greeting from any other
 *  is that it has no return path.
 *
 *  An ordinary greeting projects a response and is incomplete without one. Its
 *  grammar is adjacency: hello expects hello. Silence in reply is not a
 *  neutral outcome; it is a snub, and it is felt as one.
 *
 *  This program cannot be snubbed. It has no input. It does not read stdin,
 *  does not wait, does not check. It exits with status zero whether it was
 *  read by a thousand people or by nobody at all, and the two cases are
 *  indistinguishable from inside. It is structurally incapable of
 *  disappointment.
 *
 *  22.5  What that makes it
 *
 *  An utterance broadcast to an unspecified audience, with no expectation of
 *  reply and no mechanism to receive one, is not a conversation. The word for
 *  it is closer to one of these:
 *
 *      A prayer, which is addressed upward and outward and is not made
 *      invalid by the absence of an answer.
 *
 *      A message in a bottle, whose sender will never learn the outcome.
 *
 *      The plaque on Pioneer 10, launched in 1972 -- the same year Kernighan
 *      wrote the phrase -- carrying a diagram of two human figures with a
 *      raised hand, addressed to no one in particular, with no return channel,
 *      and now some sixteen billion kilometres out. The gesture on that plaque
 *      is a greeting. The Arecibo message of 1974 is the same act with a
 *      transmitter.
 *
 *  The similarity is structural rather than poetic. In each case: an
 *  utterance, maximally general in address, with content chosen mostly to
 *  demonstrate that the sender exists, dispatched with no expectation of and
 *  no capacity to receive a response.
 *
 *  22.6  A note on the second person
 *
 *  Emmanuel Levinas argued that ethics begins with the encounter with the face
 *  of another, and that address -- speaking to rather than about -- is the
 *  primitive ethical act, prior to any content.
 *
 *  Whatever one makes of that as philosophy, it identifies the right feature
 *  here. The program's remarkable property is not what it says but that it
 *  says it to. It performs address without an addressee. It has the form of
 *  the ethical relation and none of its substance, and it is oddly moving
 *  anyway, and Chapter 23 is about why.
 *
 * ============================================================================
 *  CHAPTER 23. SYNTAX WITHOUT SEMANTICS
 * ============================================================================
 *
 *  23.1  What is in the process
 *
 *  A complete inventory of the running program's contents, with respect to
 *  meaning:
 *
 *      A pointer to fifteen bytes of read-only data.
 *      A file descriptor, which is a small integer.
 *      A buffer.
 *      A loop that copies bytes.
 *      A system call.
 *
 *  There is no representation, anywhere in the address space, of greeting, of
 *  friendliness, of world, of anyone being addressed, or of the fact that the
 *  bytes are language at all. The same code path with different bytes would
 *  print a shopping list, a threat, or line noise, and nothing in the process
 *  would differ.
 *
 *  23.2  The Chinese Room, in its cleanest form
 *
 *  Searle's argument (1980) posits a person in a room manipulating Chinese
 *  symbols by rulebook, producing fluent Chinese output while understanding no
 *  Chinese. The claim is that syntax does not suffice for semantics.
 *
 *  The argument is usually staged against systems large enough that the
 *  intuition can be disputed -- one can always say the understanding is in the
 *  system as a whole. Here that reply is unavailable, because the whole system
 *  is visible and fits in the list above. There is no room for understanding
 *  to hide in a byte-copying loop.
 *
 *  This is the Chinese Room with the walls removed. The program produces a
 *  perfectly formed greeting in a natural language, and the complete
 *  explanation of how it does so contains no semantic content whatsoever.
 *
 *  23.3  The symbol grounding problem
 *
 *  Stevan Harnad's formulation (1990) asks how the symbols in a formal system
 *  ever connect to what they are about, if their definitions are only ever
 *  other symbols. A dictionary is circular; something must eventually touch
 *  the world.
 *
 *  In this program nothing does. The bytes are grounded in nothing. Their
 *  connection to the six-thousand-year history in Volume I exists solely in
 *  the reader. Strip away every human being and the file is a sequence of
 *  integers with a particular statistical profile.
 *
 *  23.4  The beetle in the box
 *
 *  Wittgenstein, Philosophical Investigations section 293: suppose everyone
 *  has a box containing something they call a beetle, and no one can look into
 *  anyone else's box. The word beetle cannot mean the thing in the box,
 *  because the thing in the box plays no part in the language game. Whatever
 *  is in the box "cancels out".
 *
 *  Applied here: whether there is anything it is like to be this process --
 *  and there is not, and the question is faintly ridiculous -- makes no
 *  difference to whether the greeting works. The box drops out. What remains
 *  is use, and by every external criterion actually applied to greetings, this
 *  program greets.
 *
 *  23.5  The observer supplies the meaning
 *
 *  The resolution, such as it is:
 *
 *  The meaning is not in the program. It is not in the compiler, the library
 *  or the kernel. It is in the person reading the screen, who possesses the
 *  language traced in Volume I, and who cannot help completing the act.
 *
 *  The machine performs a perfect greeting and means nothing by it. The human
 *  on the other side feels, unmistakably and against all reason, greeted. Both
 *  of these are true at once, and the second is not an error.
 *
 *  This is not a special fact about computers. It is what reading has always
 *  been. A book does not mean anything either; ink does not intend. Every text
 *  ever written is a device for causing meaning to occur in a reader, and the
 *  author is not present when it happens. The program is unusual only in being
 *  small enough that the entire mechanism can be inspected, and in the
 *  disconcerting fact that inspecting it does not stop it working.
 *
 *  23.6  A closing caution
 *
 *  It is tempting to read the argument in this chapter as debunking -- as
 *  showing that the greeting is not real. That reading is wrong, and it
 *  reverses the interesting result.
 *
 *  What the chapter shows is how little is required for a greeting to succeed.
 *  Fifteen bytes and a byte-copying loop are sufficient, provided a competent
 *  reader is present. The strong conclusion is not that the machine fails to
 *  greet. It is that greeting turns out to be a much cheaper act than anyone
 *  supposed, and that most of the work was always being done at the receiving
 *  end.
 */

/*
 * ============================================================================
 *  CHAPTER 24. RITUAL, INITIATION, AND NATALITY
 * ============================================================================
 *
 *  24.1  The one text held in common
 *
 *  Almost every programmer alive has written this program.
 *
 *  Not this program in C, necessarily -- this program in BASIC on a machine
 *  plugged into a television, or in Python in a browser tab, or in Java with
 *  six words of ceremony around it, or in Lisp, COBOL, Rust, Go, Haskell,
 *  Brainfuck, or in a language invented last week whose author wrote the
 *  greeting example before they had finished the parser.
 *
 *  The profession has no shared canon. Its literature is superseded on a
 *  decade cycle; its tools are replaced; practitioners share no formal
 *  training, no licence, no oath and no common education. There is exactly one
 *  text every member has produced, and it is fourteen bytes long.
 *
 *  24.2  It is not a technical requirement
 *
 *  There is no engineering reason for this. A first program could print the
 *  alphabet, or a multiplication table, or the date. Nothing about a toolchain
 *  requires that the first string be a greeting.
 *
 *  What is performed identically by every initiate, without technical
 *  necessity, transmitted by imitation, is not a convention. It is a rite.
 *
 *  24.3  Van Gennep's structure
 *
 *  Arnold van Gennep's Rites of Passage (1909) identifies three phases:
 *  separation from the prior state, a liminal phase in which the initiate is
 *  neither one thing nor the other, and incorporation into the new state.
 *
 *  The fit is uncomfortably exact.
 *
 *      Separation    The novice leaves the position of user. They open an
 *                    editor rather than an application. This is the moment
 *                    reported in every account as the strange one.
 *
 *      Liminality    They type words they do not understand into a file. The
 *                    include, the braces, the semicolon, the return -- none of
 *                    it can be explained yet, and every tutorial says so
 *                    explicitly: never mind what this means for now. The
 *                    initiate is required to perform correctly what they
 *                    cannot yet comprehend, which is the defining condition of
 *                    the liminal phase in every tradition van Gennep surveyed.
 *
 *      Incorporation The machine responds. Something the novice wrote caused a
 *                    machine to act. They are now, in their own estimation and
 *                    in everyone else's, a person who programs.
 *
 *  The passage is remembered. Ask any practitioner about the first time and
 *  they will have the answer ready -- the machine, the room, the year. It is
 *  filed in memory the way initiations are filed, and not the way facts are.
 *
 *  24.4  The shibboleth
 *
 *  In Judges 12 the Gileadites identify fleeing Ephraimites by requiring them
 *  to say a word whose first sound their dialect could not produce. The test
 *  has no content; the ability to perform it is the whole of the information.
 *
 *  "Hello, world" functions as the discipline's shibboleth in a gentler
 *  register. It is what a new language must produce to be taken seriously; it
 *  is the first thing shown in every announcement; and its absence from a
 *  language's documentation is noticed. The phrase is not a test of the
 *  language's power, which it cannot demonstrate. It is a test of membership.
 *
 *  24.5  The chick
 *
 *  Now the fact deferred from section 15.2.
 *
 *  The author's own account of where the phrase came from is a cartoon of a
 *  newly hatched chick saying "Hello, world!"
 *
 *  The canonical first program of the discipline is named after a birth
 *  announcement. Its governing image is a creature that has this moment come
 *  into existence, standing next to its broken shell, announcing itself to a
 *  world it has just entered and cannot yet perceive.
 *
 *  Every element of the analysis to this point falls into place under that
 *  image. The utterance with no content: a newborn has nothing to report. The
 *  addressee with no referent: a newborn does not know who is there. The
 *  absence of a return channel: a newborn cannot understand a reply. The
 *  program does not fail to be a greeting between equals. It is not one. It is
 *  the other thing, and the other thing has its own name.
 *
 *  24.6  Arendt on natality
 *
 *  Hannah Arendt, in The Human Condition (1958), makes birth rather than death
 *  the central fact of the human condition, against most of the philosophical
 *  tradition. Her term is natality: the capacity to begin, to introduce
 *  something into the world that was not there and was not entailed by what
 *  came before. Action, for Arendt, is the political faculty precisely because
 *  it is natal -- each person, being new, can start something.
 *
 *  She adds the point that matters here. To begin is to appear: action
 *  requires a public in which the actor discloses themselves, and the
 *  disclosure is inseparable from the deed. The first question the world asks
 *  of a beginning is not what it will do but that it is.
 *
 *  This is the program. It does nothing, discloses that it exists, and stops.
 *  Its whole action is appearance. And the rite in section 24.3 is a doubled
 *  natality: a process comes into existence and announces itself, and by the
 *  same act a programmer does.
 *
 * ============================================================================
 *  CHAPTER 25. MORTALITY, AND THE MEANING OF return 0
 * ============================================================================
 *
 *  25.1  The whole life
 *
 *  The program then dies. Immediately.
 *
 *  Its complete biography: it is created by a fork, it is replaced by an exec,
 *  it says one thing, and it exits. Elapsed time on modern hardware is on the
 *  order of a millisecond, most of it spent in the loader. It has one
 *  utterance and no second act.
 *
 *  25.2  The vocabulary
 *
 *  Unix describes process lifetimes in language it did not have to choose and
 *  which no one now hears.
 *
 *  A process is created by fork, which produces a child, identical to its
 *  parent, distinguished only by what it is told about itself. The child may
 *  then exec: it keeps its identity and replaces its entire contents,
 *  discarding everything it inherited. Processes have parents and children and
 *  the relation forms a tree, with one ancestor from which all descend.
 *
 *  A parent waits on its children. A child that exits while its parent is not
 *  waiting becomes a zombie: it has terminated, but its exit status has not
 *  been collected, so it cannot be removed from the table. It persists,
 *  occupying a slot, existing solely as an unacknowledged result.
 *
 *  A child whose parent dies first is an orphan. Orphans are reparented to
 *  init, the first process, which exists in part to wait for children that are
 *  not its own so that they can be released.
 *
 *  None of this terminology is required by the engineering. It could have been
 *  called deallocation and reassignment. The people who named it chose kinship
 *  and mortality, and a zombie is precisely a death that no one has
 *  acknowledged.
 *
 *  25.3  Zero
 *
 *  The program returns 0 to its parent.
 *
 *  By convention -- and only by convention; nothing enforces it -- zero means
 *  success and any other value means a failure of a kind the program chose to
 *  distinguish. The shell reads it. Almost nothing else does. It is a single
 *  small integer and it is the entirety of what the system asks.
 *
 *  Consider what this means as an evaluation. A process runs, does whatever it
 *  does, and at the end renders its life into one number, and the number does
 *  not record what was accomplished. Zero does not mean the work was good, or
 *  useful, or correct. Zero means: nothing went wrong.
 *
 *  A complete life, assessed on exactly one criterion, and the criterion is
 *  not achievement but the absence of error. The program cannot report that it
 *  greeted the world. It can only report that it did not fail to.
 *
 *  There is an asymmetry here worth naming. Failure is expressive -- 256
 *  values, conventions for signals, a whole vocabulary of ways to have gone
 *  wrong. Success has one value and no detail. The system is built to hear
 *  about problems and is entirely uninterested in what went right, which is a
 *  design that will be familiar to anyone who has held a job.
 *
 *  25.4  The newline
 *
 *  Section 18.5 gave the engineering account of the trailing newline: it
 *  flushes a line-buffered stream, so the output appears now rather than at
 *  exit.
 *
 *  The other account is that the newline is the program relinquishing the
 *  line.
 *
 *  A program that omits it leaves the cursor sitting at the end of its own
 *  output, and the shell prompt appears jammed against the final character.
 *  The effect on a terminal is of someone who has finished speaking and not
 *  stopped. The newline is what returns the floor to whoever comes next.
 *
 *  It is the last thing the process does, and it is an act of yielding rather
 *  than of speech. The program says its one sentence, gives back the line, and
 *  reports that nothing went wrong. The whole shape of the thing is in the
 *  final byte.
 *
 *  25.5  On the largest scale
 *
 *  This program has been run, at a conservative estimate, more times than any
 *  other program ever written, on hardware that no longer exists, by people
 *  who are no longer alive, in languages that have fallen out of use.
 *
 *  Each instance lived about a millisecond, said one thing, and exited zero.
 *  None of them left anything behind. The file remains, and the sentence
 *  remains, and every process that has ever uttered it is gone.
 *
 *  Whether that is melancholy or not is left to the reader. It is, at minimum,
 *  the most-repeated utterance in the history of machines, and every single
 *  utterance of it was made by something that ceased to exist immediately
 *  afterward and was never answered.
 *
 * ============================================================================
 *  CHAPTER 26. CONCLUSION
 * ============================================================================
 *
 *  26.1  The descent, restated
 *
 *  Around six thousand years ago, on the steppe north of the Black Sea, people
 *  who left no writing used a word for a man and a word for growing old.
 *
 *  Their descendants carried both northwest. In Germanic mouths the consonants
 *  shifted and the stress moved to the front of the word, which set a slow
 *  erosion running through the ends of words that would take two thousand
 *  years to finish. In Anglo-Saxon England the two words were welded into a
 *  compound meaning the age of man -- not the planet, but the human situation,
 *  considered as a span of time one is inside of and will leave.
 *
 *  Norse settlers wore the grammar down. Norman French replaced the ruling
 *  class and English went unwritten for three centuries and came out the other
 *  side without its endings, needing word order to carry what the endings had
 *  carried. The vowels all moved. A printing press froze the spelling
 *  mid-movement. Empire and then industry and then the network carried the
 *  result everywhere.
 *
 *  Meanwhile a shout -- used for hailing a ferryman, urging a hound, stopping a
 *  stranger at a distance -- was drafted, in the 1870s, to solve the problem of
 *  addressing someone at the far end of a wire whose presence could not
 *  otherwise be confirmed. Edison preferred it to Bell's "Ahoy" and the
 *  exchange manuals settled the matter.
 *
 *  In 1969 an operating system project collapsed and left a small group at
 *  Bell Labs with time, a cast-off machine, and clear ideas. They built a
 *  system; the system needed a language; the language needed types; the
 *  language got them; and in 1973 they rewrote the system in it, which made
 *  operating systems portable, which is why the language is now underneath
 *  nearly everything.
 *
 *  In 1972 one of them, writing a tutorial, needed a first example. He used
 *  two English words -- one a hailing-cry a century old, one a compound six
 *  millennia old -- and by his own account he got them from a cartoon of a
 *  chick that had just hatched.
 *
 *  26.2  What it means
 *
 *  It means nothing. That is not a failure of the sentence; it is its
 *  function, and everything else follows from it.
 *
 *  It is phatic: content deliberately emptied so that the channel is the whole
 *  message. It is an existence proof: fourteen bytes that certify a
 *  fifty-year tower of abstractions is standing. It is a speech act that fails
 *  every felicity condition and works anyway, because greeting turns out to be
 *  conferred by the receiver rather than possessed by the speaker. It is
 *  addressed to a vocative with no referent, with no channel for reply, which
 *  places it nearer to prayer and to the Pioneer plaque than to conversation.
 *  It is the discipline's only shared text and its rite of initiation. It is,
 *  by its author's account, a birth announcement. And it ends with one
 *  utterance, a relinquished line, and a single integer reporting that nothing
 *  went wrong.
 *
 *  26.3  The thesis, finally
 *
 *  Before we teach a machine to compute, we teach it to make contact.
 *
 *  The first thing every programmer causes a machine to do is not to solve
 *  anything but to declare that a channel is open and something is at this end
 *  of it. We do this by reflex, without deciding to, and we have done it
 *  identically for fifty years in every language we have built.
 *
 *  That is the finding of this dissertation, and it is the reason the sentence
 *  has outlived the machine it was written on, the language it was written
 *  for, the company that employed its author, and very nearly everyone who
 *  read it first.
 *
 *  It is the sound the tower makes when all of it is working:
 *
 *          that a channel is open, and that something is at this end of it.
 *
 *  END OF VOLUME III.
 */

/*
 * ############################################################################
 * #                              APPENDICES                                   #
 * ############################################################################
 *
 * ============================================================================
 *  APPENDIX A. THE SENTENCE IN OTHER TONGUES
 * ============================================================================
 *
 *  The greeting is not usually translated when the language of the program is
 *  not English -- see section 7.5 -- but the sentence itself has standard
 *  renderings, and the second word is instructive in each case.
 *
 *      Language      Rendering                 The word for "world"
 *      --------      ---------                 --------------------
 *      German        Hallo, Welt!              Welt < weralt, the same
 *                                              *weraldiz compound as English
 *      Dutch         Hallo, wereld!            wereld, same compound
 *      Icelandic     Hallo, heimur!            heimur, "home, abode" -- a
 *                                              different metaphor entirely,
 *                                              though verold also exists
 *      French        Bonjour, monde !          monde < Latin mundus, "the
 *                                              ordered cosmos"; unrelated
 *      Spanish       Hola, mundo!              same Latin root
 *      Latin         Salve, munde!             mundus in the vocative, which
 *                                              English can no longer mark
 *      Russian       Privet, mir!              mir, which also means "peace"
 *                                              and "the village commune"
 *      Greek         Geia sou, kosme!          kosmos, "order, arrangement";
 *                                              the opposite of chaos
 *      Japanese      Sekai, konnichiwa         sekai, from Buddhist Sanskrit
 *                                              via Chinese: loka-dhatu, the
 *                                              realm of transmigration
 *      Chinese       Ni hao, shijie            shijie, the same two characters
 *                                              as Japanese sekai: "generation"
 *                                              plus "boundary"
 *      Arabic        Marhaban ya alam          alam, from a root meaning "to
 *                                              know" -- that by which the
 *                                              creator is known
 *      Hebrew        Shalom olam               olam, which in Biblical Hebrew
 *                                              means primarily an age or
 *                                              eternity, not a place
 *
 *  The pattern is worth noting. Three quite different metaphors recur:
 *
 *      the world as a span of time      English weorold, Hebrew olam,
 *                                       Japanese and Chinese "generation"
 *      the world as an arrangement      Greek kosmos, Latin mundus
 *      the world as a dwelling          Icelandic heimur
 *
 *  English and Hebrew arrive independently at the same figure: the world is
 *  an age. Greek and Latin agree on a different one: the world is an order.
 *  The choice of metaphor is not available to the programmer, who inherits
 *  whichever one their language settled on before they were born.
 *
 * ============================================================================
 *  APPENDIX B. CHRONOLOGY
 * ============================================================================
 *
 *      c. 4500-2500 BCE   Proto-Indo-European. *wi-ro- "man", *al- "age"
 *      c. 500 BCE         Proto-Germanic. Grimm's Law; stress fixed initially
 *      c. 100 CE          Latin trade loans: wine, street, mile, pound
 *      410                Roman withdrawal from Britain
 *      c. 450             Anglo-Saxon settlement begins
 *      597                Augustine in Kent; Roman alphabet; Latin loans
 *      c. 700-1000        weorold attested throughout the corpus
 *      793                Lindisfarne; the Norse contact begins
 *      c. 878             Danelaw established; inflectional collapse begins
 *      1066               Hastings. English stops being written
 *      c. 1150-1470       Middle English; ~10,000 French words
 *      c. 1387            Chaucer begins the Canterbury Tales in English
 *      c. 1400-1700       The Great Vowel Shift
 *      1476               Caxton's press at Westminster; spelling freezes
 *      1611               King James Bible
 *      1755               Johnson's Dictionary
 *      c. 1826            "hullo" and relatives attested as hailing-cries
 *      1877               Edison proposes "Hello" for the telephone
 *      1878               First telephone directory, New Haven
 *      1949-55            Assemblers and autocodes; Hopper's A-0
 *      1957               FORTRAN
 *      1960               ALGOL 60; Backus-Naur Form
 *      1963               CPL. ASCII standardized
 *      1964               Multics begins
 *      1967               BCPL
 *      1969               Bell Labs withdraws from Multics. Unix on the PDP-7.
 *                         B
 *      1970               PDP-11 arrives; byte addressing forces types
 *      1972               C. Kernighan's B tutorial: "hello, world".
 *                         Pioneer 10 launched with its plaque
 *      1973               Unix kernel rewritten in C. Pipes
 *      1974               Kernighan's C tutorial. Arecibo message
 *      1976               Lions's Commentary
 *      1977-78            Unix ported to the Interdata 8/32
 *      1978               K&R, first edition. VT100
 *      1989               ANSI C (C89)
 *      1990               ISO C90. Lions's book still photocopied
 *      1999               C99
 *      2011               C11. Dennis Ritchie dies, 12 October
 *      2017               C17
 *      2023               C23; K&R declarations removed from the language
 *      2026               This file
 *
 * ============================================================================
 *  APPENDIX C. GLOSSARY
 * ============================================================================
 *
 *      ablaut          Vowel alternation inherited from PIE that carries
 *                      grammatical meaning: sing/sang/sung
 *      ABI             Application Binary Interface: the platform agreement on
 *                      how compiled code calls compiled code
 *      cognate         Two words descended from one ancestral word, as against
 *                      one borrowed from the other
 *      doublet         Two words in one language from one ancestor by two
 *                      routes: shirt and skirt
 *      felicity        In Austin, the conditions under which a performative
 *      conditions      utterance succeeds in performing its act
 *      i-mutation      Fronting of a root vowel under influence of a following
 *                      i that has since vanished: foot/feet
 *      kenning         Old English compressed metaphorical compound:
 *                      whale-road for the sea
 *      liminality      Van Gennep's middle phase of a rite of passage, in
 *                      which the initiate is neither the old thing nor the new
 *      natality        Arendt's term for the human capacity to begin
 *      phatic          Malinowski's term for speech whose function is contact
 *                      rather than content
 *      performative    An utterance that performs the act it names rather than
 *                      describing a state of affairs
 *      PIE             Proto-Indo-European
 *      undefined       Program behaviour on which the C standard imposes no
 *      behaviour       requirement whatsoever
 *      vocative        The grammatical form of direct address; in English,
 *                      marked only by the comma
 *
 * ============================================================================
 *  APPENDIX D. ON WHAT HAS BEEN OMITTED
 * ============================================================================
 *
 *  Honesty about scope. This dissertation does not treat:
 *
 *  The Celtic substrate question, which is genuinely unresolved and which
 *  bears on why English lost its inflections earlier and harder than its
 *  siblings. Some argue Brittonic influence explains the do-support of
 *  section 7.2 and the progressive aspect; the case is not settled and could
 *  not be settled in a comment.
 *
 *  Sociolinguistics entirely. Nothing here addresses who is permitted to
 *  speak the standard, what a prestige dialect costs its non-speakers, or
 *  the politics of the paragraph in section 7.5 that treats English's
 *  incumbency in computing as a mere accident. It was an accident with
 *  beneficiaries.
 *
 *  The alternatives to C. Ada was safer and lost. Pascal was cleaner and lost.
 *  The counterfactual in which the industry standardized on a memory-safe
 *  systems language in 1975 is the most expensive road not taken in the
 *  history of the field, and Chapter 13 gestures at it in a paragraph.
 *
 *  Any serious treatment of whether the machine could mean it. Chapter 23
 *  takes a position -- that the meaning is supplied entirely by the reader --
 *  and does not defend it against the functionalist reply, which deserves
 *  better than the two sentences it gets.
 *
 *  Every other first program. BASIC's PRINT "HELLO", the LOGO turtle, Smalltalk
 *  Transcript show, and the Lisp REPL that greets you before you type anything
 *  each have their own history, and the REPL in particular inverts the whole
 *  analysis by having the machine speak first.
 *
 *  Any assessment of whether a program of six lines warrants a treatment
 *  of this length. The question is a fair one and is not addressed.
 *
 * ############################################################################
 * #                                                                          #
 * #                              THE PROGRAM                                  #
 * #                                                                          #
 * #  Everything above is deleted at translation phase 3 (section 18.1) and    #
 * #  has no effect whatsoever on the following six lines, which are the       #
 * #  entirety of what the machine will be told.                               #
 * #                                                                          #
 * ############################################################################
 */

#include <stdio.h>   /* declares printf; see section 18.2 */

int main(void)
{
    printf("Hello, World!\n");   /* Vol. I: the sentence. Vol. II: the call. */

    return 0;                    /* nothing went wrong; see section 25.3 */
}
