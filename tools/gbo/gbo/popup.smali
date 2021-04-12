.class public Lcom/gbo/popup;
.super Ljava/lang/Object;


# direct methods
.method public constructor <init>()V
    .locals 0

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method

.method public static Start(Landroid/content/Context;)V
    .locals 2

    invoke-static {p0}, Lcom/gbo/popup;->gboCustomMessage(Landroid/content/Context;)V
	
    return-void
.end method

.method public static gboCustomMessage(Landroid/content/Context;)V
    .locals 5

    new-instance v0, Landroid/app/AlertDialog$Builder;

    invoke-direct {v0, p0}, Landroid/app/AlertDialog$Builder;-><init>(Landroid/content/Context;)V

    new-instance v1, Landroid/widget/TextView;

    invoke-direct {v1, p0}, Landroid/widget/TextView;-><init>(Landroid/content/Context;)V

    new-instance v2, Landroid/widget/TextView;

    invoke-direct {v2, p0}, Landroid/widget/TextView;-><init>(Landroid/content/Context;)V

    const-string v3, "<b><font color=blue><u>Jbro129\'s 12.2.1 PG3D Mod</u></font></b>"

    invoke-static {v3}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v3

    invoke-virtual {v1, v3}, Landroid/widget/TextView;->setText(Ljava/lang/CharSequence;)V

    const/16 v3, 0xa

    invoke-virtual {v1, v3, v3, v3, v3}, Landroid/widget/TextView;->setPadding(IIII)V

    const/4 v3, 0x1

    invoke-virtual {v1, v3}, Landroid/widget/TextView;->setGravity(I)V

    const/high16 v3, 0x41a00000    # 20.0f

    invoke-virtual {v1, v3}, Landroid/widget/TextView;->setTextSize(F)V

    const-string v3, "<b>&#8594; AntiBan V3 (Root, Speed, and Time Tampering Undetected)  &#8592;<br/>&#8594; Player Mod (Gadget Spam V2, GodMode, and Infinite Flight) &#8592;<br/>&#8594; Everthing In Shop Is Free (0 <font color=#fff105>Coins</font> & 0 <font color=#55d3ff>Gems</font>) &#8592;<br/>&#8594; Miscellaneous (Max Ammo, Infinite Pet Points, and More!) &#8592;<br/>&#8594; <font color=#C602CD>Mythical</font> Pets Easier To Get &#8592;<br/><br/><i><font color=\u201d0000FF\u201d>&#9578;</font>Credits to<font color=\u201d0000FF\u201d>&#9578</a></font></i></b><br/><br/><font color=#FFA500><a href=https://www.youtube.com/channel/UC1qWCyC38t0dtXRB2d-3t9g><div>&#10028;<font color=#ff0000>J</font><font color=#da6924>b</font><font color=#b6c048>r</font><font color=#91f46d>o</font><font color=#6dfc91>1</font><font color=#48d6b6>2</font><font color=#2489da>9</font>&#10028;</div><a href=https://www.youtube.com/channel/UC1qWCyC38t0dtXRB2d-3t9g><font color=#32B232>Subscribe :)<a></font><br><br/><font color=#ff0000><b> PLEASE GIVE CREDITS TO JBRO129 IF UPLOADING TO YOUTUBE!!!<b/><font/>"

    invoke-static {v3}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v3

    invoke-virtual {v2, v3}, Landroid/widget/TextView;->setText(Ljava/lang/CharSequence;)V

    const/16 v3, 0xa

    invoke-virtual {v2, v3, v3, v3, v3}, Landroid/widget/TextView;->setPadding(IIII)V

    const/4 v3, 0x1

    invoke-virtual {v2, v3}, Landroid/widget/TextView;->setGravity(I)V

    const/high16 v3, 0x41a00000    # 20.0f

    invoke-virtual {v1, v3}, Landroid/widget/TextView;->setTextSize(F)V

    const/4 v3, 0x0

    invoke-virtual {v0, v3}, Landroid/app/AlertDialog$Builder;->setCancelable(Z)Landroid/app/AlertDialog$Builder;

    const-string v3, "&#9604;&#9604;&#9604;&#9604;&#9604;&#9604;&#9604;&#9604;&#9604;&#9604;<br>&#9608;<font color=red>  C O N T I N U E     </font>&#9608;<br/>&#9600;&#9600;&#9600;&#9600;&#9600;&#9600;&#9600;&#9600;&#9600;&#9600;"

    invoke-static {v3}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v3

    const/4 v4, 0x0

    invoke-virtual {v0, v3, v4}, Landroid/app/AlertDialog$Builder;->setPositiveButton(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;

    invoke-virtual {v0, v1}, Landroid/app/AlertDialog$Builder;->setCustomTitle(Landroid/view/View;)Landroid/app/AlertDialog$Builder;

    invoke-virtual {v0, v2}, Landroid/app/AlertDialog$Builder;->setView(Landroid/view/View;)Landroid/app/AlertDialog$Builder;

    invoke-virtual {v0}, Landroid/app/AlertDialog$Builder;->show()Landroid/app/AlertDialog;

    invoke-static {}, Landroid/text/method/LinkMovementMethod;->getInstance()Landroid/text/method/MovementMethod;

    move-result-object v3

    invoke-virtual {v2, v3}, Landroid/widget/TextView;->setMovementMethod(Landroid/text/method/MovementMethod;)V

    return-void
.end method